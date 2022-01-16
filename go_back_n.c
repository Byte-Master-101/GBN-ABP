#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional or bidirectional
   data transfer protocols (from A to B. Bidirectional transfer of data
   is for extra credit and is not required).  Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
     (although some can be lost).
**********************************************************************/

#define BIDIRECTIONAL 0    /* change to 1 if you're doing extra credit */
                           /* and write a routine called B_output */

/* a "msg" is the data unit passed from layer 5 (teachers code) to layer  */
/* 4 (students' code).  It contains the data (characters) to be delivered */
/* to layer 5 via the students transport level protocol entities.         */
struct msg {
  char data[20];
  };

/* a packet is the data unit passed from layer 4 (students code) to layer */
/* 3 (teachers code).  Note the pre-defined packet structure, which all   */
/* students must follow. */
struct pkt {
   int seqnum;
   int acknum;
   int checksum;
   char payload[20];
    };

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
#define A            0
#define B            1
#define WINDOW       6
#define TIMEOUT      25
#define ABORT(str)   { printf(str "! Aborting connection..."); exit(1); }

// #define COLORED_TERM
#ifdef COLORED_TERM
// https://www.theurbanpenguin.com/4184-2/
#define A_PREFIX  "\033[0;31m[A] "
#define B_PREFIX  "\033[0;36m[B] "
#define POSTFIX   "\033[0m"
#else
#define  A_PREFIX "[A] "
#define  B_PREFIX "[B] "
#define POSTFIX   ""
#endif

void starttimer(int AorB, float increment);
void stoptimer(int AorB);
void init();
void generate_next_arrival();
void tolayer3(int AorB, struct pkt packet);
void tolayer5(int AorB, char datasent[20]);

struct node
{
   struct node *next;
   struct pkt packet;
};

struct node *A_packets_tail;
int A_next_seq;
bool A_timer_running;

int B_next_seq;

int calculate_checksum(struct pkt packet)
{
   int checksum = 0;
   checksum += packet.seqnum;
   checksum += packet.acknum;
   // checksum += packet.checksum; // Might be considered as a seed
   
   int *payload = (int*)(packet.payload);
   for (size_t i = 0; i < sizeof(packet.payload)/sizeof(*payload); i++)
      checksum += payload[i];
   
   return ~checksum;
}

void set_packet_checksum(struct pkt *packet)
{
   packet->checksum = calculate_checksum(*packet);
}

bool check_packet_checksum(struct pkt packet)
{
   return packet.checksum == calculate_checksum(packet);
}

/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
   struct node *new_node = (struct node *)malloc(sizeof(struct node));
   new_node->next = 0;
   new_node->packet.seqnum = A_next_seq++;
   new_node->packet.acknum = -1;
   new_node->packet.checksum = 0;
   memcpy(new_node->packet.payload, message.data, sizeof(new_node->packet.payload));
   set_packet_checksum(&new_node->packet);

   bool window_empty = A_packets_tail == 0;
   if(window_empty)
   {
      new_node->next = new_node;
      A_packets_tail = new_node;
   }
   else
   {
      new_node->next = A_packets_tail->next;
      A_packets_tail->next = new_node;
      A_packets_tail = new_node;
   }

   if(A_packets_tail->packet.seqnum - A_packets_tail->next->packet.seqnum + 1 > WINDOW)
   {
      printf(A_PREFIX "STOR: Packet %d\n" POSTFIX, A_packets_tail->packet.seqnum);
      return;
   }

   printf(A_PREFIX "SEND: Packet %d\n" POSTFIX, new_node->packet.seqnum);
   tolayer3(A, new_node->packet);

   if(window_empty)
   {
      printf(A_PREFIX "TIME: Start\n" POSTFIX);
      starttimer(A, TIMEOUT);
   }
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
   if(!check_packet_checksum(packet))
   {
      printf(A_PREFIX "DROP: Packet Invalid\n" POSTFIX);
      return;
   };

   printf(A_PREFIX " ACK: Packet %d\n" POSTFIX, packet.acknum);
   if(A_packets_tail == 0) return;

   int acked = 0;

   struct node *head = A_packets_tail->next;
   while(head->packet.seqnum <= packet.acknum)
   {
      if(head == A_packets_tail)
      {
         free(A_packets_tail);
         A_packets_tail = 0;

         printf(A_PREFIX "TIME: Stop\n" POSTFIX);
         stoptimer(A);

         return;
      }

      struct node *old_head = head;
      head = head->next;
      A_packets_tail->next = head;
      free(old_head);
      
      acked++;
   }

   if(acked > 0)
   {
      printf(A_PREFIX "TIME: Restart\n" POSTFIX);
      stoptimer(A);
      starttimer(A, TIMEOUT);
   }

   struct node *unsent = head;
   for (size_t i = 0; i < WINDOW - acked; i++)
   {
      if(unsent == A_packets_tail) return; // No unsent packets
      unsent = unsent->next;
   }

   for (size_t i = 0; i < acked; i++)
   {
      printf(A_PREFIX "SEND: Packet %d\n" POSTFIX, unsent->packet.seqnum);
      tolayer3(A, unsent->packet);
      // if(i == 0) starttimer(A, TIMEOUT);

      if(unsent == A_packets_tail) return; // No more unsent packets
      unsent = unsent->next;
   }
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
   printf(A_PREFIX "TIME: Timeout\n" POSTFIX);
   starttimer(A, TIMEOUT);

   struct node *unsent = A_packets_tail->next;
   for (size_t i = 0; i < WINDOW; i++)
   {
      printf(A_PREFIX "RSND: Packet %d\n" POSTFIX, unsent->packet.seqnum);
      tolayer3(A, unsent->packet);

      if(unsent == A_packets_tail) return; // No more unsent packets
      unsent = unsent->next;
   }
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
   A_next_seq = 0;

   printf("\n");
}

void B_output(struct msg message)
{
   ABORT("Function B_output not implemented")
}

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
   if(!check_packet_checksum(packet))
   {
      printf(B_PREFIX "DROP: Packet Invalid\n" POSTFIX);
      return;
   };

   if(packet.seqnum > B_next_seq)
   {
      printf(B_PREFIX "DROP: Packet %d\n" POSTFIX, packet.seqnum);
      return;
   };

   int acknum = B_next_seq - 1;
   if(packet.seqnum == B_next_seq)
   {
      printf(B_PREFIX "RECV: Packet %d [%.20s]\n" POSTFIX, packet.seqnum, packet.payload);

      acknum++;
      B_next_seq++;
      tolayer5(B, packet.payload);
   }
   else
      printf(B_PREFIX " DUP: Packet %d\n" POSTFIX, packet.seqnum);

   struct pkt ack_packet = {
      .seqnum = -1,
      .acknum = acknum,
      .checksum = 0,
      .payload = ""
   };
   set_packet_checksum(&ack_packet);

   printf(B_PREFIX "ASND: Packet %d\n" POSTFIX, ack_packet.acknum);
   tolayer3(B, ack_packet);
}

void B_timerinterrupt()
{
   ABORT("Function B_timerinterrupt not implemented")
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
   B_next_seq = 0;
}

/*****************************************************************
***************** NETWORK EMULATION CODE STARTS BELOW ***********
The code below emulates the layer 3 and below network environment:
  - emulates the tranmission and delivery (possibly with bit-level corruption
    and packet loss) of packets across the layer 3/4 interface
  - handles the starting/stopping of a timer, and generates timer
    interrupts (resulting in calling students timer handler).
  - generates message to be sent (passed from later 5 to 4)

THERE IS NOT REASON THAT ANY STUDENT SHOULD HAVE TO READ OR UNDERSTAND
THE CODE BELOW.  YOU SHOLD NOT TOUCH, OR REFERENCE (in your code) ANY
OF THE DATA STRUCTURES BELOW.  If you're interested in how I designed
the emulator, you're welcome to look at the code - but again, you should have
to, and you defeinitely should not have to modify
******************************************************************/

struct event {
   float evtime;           /* event time */
   int evtype;             /* event type code */
   int eventity;           /* entity where event occurs */
   struct pkt *pktptr;     /* ptr to packet (if any) assoc w/ this event */
   struct event *prev;
   struct event *next;
 };
struct event *evlist = NULL;   /* the event list */

/* possible events: */
#define  TIMER_INTERRUPT 0
#define  FROM_LAYER5     1
#define  FROM_LAYER3     2

#define  OFF             0
#define  ON              1
// #define   A    0
// #define   B    1



int TRACE = 1;             /* for my debugging */
int nsim = 0;              /* number of messages from 5 to 4 so far */
int nsimmax = 0;           /* number of msgs to generate, then stop */
float time = 0.000;
float lossprob;            /* probability that a packet is dropped  */
float corruptprob;         /* probability that one bit is packet is flipped */
float lambda;              /* arrival rate of messages from layer 5 */
int   ntolayer3;           /* number sent into layer 3 */
int   nlost;               /* number lost in media */
int ncorrupt;              /* number corrupted by media*/

int main()
{
   struct event *eventptr;
   struct msg  msg2give;
   struct pkt  pkt2give;

   int i,j;
   char c;

   init();
   A_init();
   B_init();

   while (1) {
        eventptr = evlist;            /* get next event to simulate */
        if (eventptr==NULL)
           goto terminate;
        evlist = evlist->next;        /* remove this event from event list */
        if (evlist!=NULL)
           evlist->prev=NULL;
        if (TRACE>=2) {
           printf("\nEVENT time: %f,",eventptr->evtime);
           printf("  type: %d",eventptr->evtype);
           if (eventptr->evtype==0)
	       printf(", timerinterrupt  ");
             else if (eventptr->evtype==1)
               printf(", fromlayer5 ");
             else
	     printf(", fromlayer3 ");
           printf(" entity: %d\n",eventptr->eventity);
           }
        time = eventptr->evtime;        /* update time to next event time */
   //      if (nsim==nsimmax)
	//   break;                        /* all done with simulation */
        if (eventptr->evtype == FROM_LAYER5 ) {
           if(nsim < nsimmax)
           {
            generate_next_arrival();   /* set up future arrival */
            /* fill in msg to give with string of same letter */
            j = nsim % 26;
            for (i=0; i<20; i++)
               msg2give.data[i] = 97 + j;
            if (TRACE>2) {
               printf("          MAINLOOP: data given to student: ");
                 for (i=0; i<20; i++)
                  printf("%c", msg2give.data[i]);
               printf("\n");
            }
            nsim++;
            if (eventptr->eventity == A)
               A_output(msg2give);
             else
               B_output(msg2give);
            }
	     }
          else if (eventptr->evtype ==  FROM_LAYER3) {
            pkt2give.seqnum = eventptr->pktptr->seqnum;
            pkt2give.acknum = eventptr->pktptr->acknum;
            pkt2give.checksum = eventptr->pktptr->checksum;
            for (i=0; i<20; i++)
                pkt2give.payload[i] = eventptr->pktptr->payload[i];
	    if (eventptr->eventity ==A)      /* deliver packet by calling */
   	       A_input(pkt2give);            /* appropriate entity */
            else
   	       B_input(pkt2give);
	    free(eventptr->pktptr);          /* free the memory for packet */
            }
          else if (eventptr->evtype ==  TIMER_INTERRUPT) {
            if (eventptr->eventity == A)
	       A_timerinterrupt();
             else
	       B_timerinterrupt();
             }
          else  {
	     printf("INTERNAL PANIC: unknown event type \n");
             }
        free(eventptr);
        }

terminate:
   printf(" Simulator terminated at time %f\n after sending %d msgs from layer5\n",time,nsim);
   return 0;
}



void init()                         /* initialize the simulator */
{
  int i;
  float sum, avg;
  float jimsrand();


   printf("-----  Stop and Wait Network Simulator Version 1.1 -------- \n\n");
   printf("Enter the number of messages to simulate: ");
   scanf("%d",&nsimmax);
   printf("Enter  packet loss probability [enter 0.0 for no loss]:");
   scanf("%f",&lossprob);
   printf("Enter packet corruption probability [0.0 for no corruption]:");
   scanf("%f",&corruptprob);
   printf("Enter average time between messages from sender's layer5 [ > 0.0]:");
   scanf("%f",&lambda);
   printf("Enter TRACE:");
   scanf("%d",&TRACE);

   srand(9999);              /* init random number generator */
   sum = 0.0;                /* test random number generator for students */
   for (i=0; i<1000; i++)
      sum=sum+jimsrand();    /* jimsrand() should be uniform in [0,1] */
   avg = sum/1000.0;
   if (avg < 0.25 || avg > 0.75) {
    printf("It is likely that random number generation on your machine\n" );
    printf("is different from what this emulator expects.  Please take\n");
    printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
    exit(0);
    }

   ntolayer3 = 0;
   nlost = 0;
   ncorrupt = 0;

   time=0.0;                    /* initialize time to 0.0 */
   generate_next_arrival();     /* initialize event list */
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand()
{
  double mmm = (double) RAND_MAX ;//2147483647;   /* largest int  - MACHINE DEPENDENT!!!!!!!!   */
  float x;                   /* individual students may need to change mmm */
  x = rand()/mmm;            /* x should be uniform in [0,1] */
  return(x);
}

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/
void insertevent(struct event *p);

void generate_next_arrival()
{
   double x,log(),ceil();
   struct event *evptr;
//   char *malloc();
   float ttime;
   int tempint;

   if (TRACE>2)
       printf("          GENERATE NEXT ARRIVAL: creating new arrival\n");

   x = lambda*jimsrand()*2;  /* x is uniform on [0,2*lambda] */
                             /* having mean of lambda        */
   evptr = (struct event *)malloc(sizeof(struct event));
   evptr->evtime =  time + x;
   evptr->evtype =  FROM_LAYER5;
   if (BIDIRECTIONAL && (jimsrand()>0.5) )
      evptr->eventity = B;
    else
      evptr->eventity = A;
   insertevent(evptr);
}


void insertevent(struct event *p)
{
   struct event *q,*qold;

   if (TRACE>2) {
      printf("            INSERTEVENT: time is %lf\n",time);
      printf("            INSERTEVENT: future time will be %lf\n",p->evtime);
      }
   q = evlist;     /* q points to header of list in which p struct inserted */
   if (q==NULL) {   /* list is empty */
        evlist=p;
        p->next=NULL;
        p->prev=NULL;
        }
     else {
        for (qold = q; q !=NULL && p->evtime > q->evtime; q=q->next)
              qold=q;
        if (q==NULL) {   /* end of list */
             qold->next = p;
             p->prev = qold;
             p->next = NULL;
             }
           else if (q==evlist) { /* front of list */
             p->next=evlist;
             p->prev=NULL;
             p->next->prev=p;
             evlist = p;
             }
           else {     /* middle of list */
             p->next=q;
             p->prev=q->prev;
             q->prev->next=p;
             q->prev=p;
             }
         }
}

void printevlist()
{
  struct event *q;
  int i;
  printf("--------------\nEvent List Follows:\n");
  for(q = evlist; q!=NULL; q=q->next) {
    printf("Event time: %f, type: %d entity: %d\n",q->evtime,q->evtype,q->eventity);
    }
  printf("--------------\n");
}



/********************** Student-callable ROUTINES ***********************/

/* called by students routine to cancel a previously-started timer */
void stoptimer(int AorB) /* A or B is trying to stop timer */
{
 struct event *q,*qold;

 if (TRACE>2)
    printf("          STOP TIMER: stopping timer at %f\n",time);
/* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
 for (q=evlist; q!=NULL ; q = q->next)
    if ( (q->evtype==TIMER_INTERRUPT  && q->eventity==AorB) ) {
       /* remove this event */
       if (q->next==NULL && q->prev==NULL)
             evlist=NULL;         /* remove first and only event on list */
          else if (q->next==NULL) /* end of list - there is one in front */
             q->prev->next = NULL;
          else if (q==evlist) { /* front of list - there must be event after */
             q->next->prev=NULL;
             evlist = q->next;
             }
           else {     /* middle of list */
             q->next->prev = q->prev;
             q->prev->next =  q->next;
             }
       free(q);
       return;
     }
  printf("Warning: unable to cancel your timer. It wasn't running.\n");
}


void starttimer(int AorB, float increment) /* A or B is trying to stop timer */
{

 struct event *q;
 struct event *evptr;
// char *malloc();

 if (TRACE>2)
    printf("          START TIMER: starting timer at %f\n",time);
 /* be nice: check to see if timer is already started, if so, then  warn */
/* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
   for (q=evlist; q!=NULL ; q = q->next)
    if ( (q->evtype==TIMER_INTERRUPT  && q->eventity==AorB) ) {
      printf("Warning: attempt to start a timer that is already started\n");
      return;
      }

/* create future event for when timer goes off */
   evptr = (struct event *)malloc(sizeof(struct event));
   evptr->evtime =  time + increment;
   evptr->evtype =  TIMER_INTERRUPT;
   evptr->eventity = AorB;
   insertevent(evptr);
}


/************************** TOLAYER3 ***************/
void tolayer3(int AorB, struct pkt packet) /* A or B is trying to stop timer */
{
 struct pkt *mypktptr;
 struct event *evptr,*q;
// char *malloc();
 float lastime, x, jimsrand();
 int i;


 ntolayer3++;

 /* simulate losses: */
 if (jimsrand() < lossprob)  {
      nlost++;
      if (TRACE>0)
	printf("          TOLAYER3: packet being lost\n");
      return;
    }

/* make a copy of the packet student just gave me since he/she may decide */
/* to do something with the packet after we return back to him/her */
 mypktptr = (struct pkt *)malloc(sizeof(struct pkt));
 mypktptr->seqnum = packet.seqnum;
 mypktptr->acknum = packet.acknum;
 mypktptr->checksum = packet.checksum;
 for (i=0; i<20; i++)
    mypktptr->payload[i] = packet.payload[i];
 if (TRACE>2)  {
   printf("          TOLAYER3: seq: %d, ack %d, check: %d ", mypktptr->seqnum,
	  mypktptr->acknum,  mypktptr->checksum);
    for (i=0; i<20; i++)
        printf("%c",mypktptr->payload[i]);
    printf("\n");
   }

/* create future event for arrival of packet at the other side */
  evptr = (struct event *)malloc(sizeof(struct event));
  evptr->evtype =  FROM_LAYER3;   /* packet will pop out from layer3 */
  evptr->eventity = (AorB+1) % 2; /* event occurs at other entity */
  evptr->pktptr = mypktptr;       /* save ptr to my copy of packet */
/* finally, compute the arrival time of packet at the other end.
   medium can not reorder, so make sure packet arrives between 1 and 10
   time units after the latest arrival time of packets
   currently in the medium on their way to the destination */
 lastime = time;
/* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next) */
 for (q=evlist; q!=NULL ; q = q->next)
    if ( (q->evtype==FROM_LAYER3  && q->eventity==evptr->eventity) )
      lastime = q->evtime;
 evptr->evtime =  lastime + 1 + 9*jimsrand();



 /* simulate corruption: */
 if (jimsrand() < corruptprob)  {
    ncorrupt++;
    if ( (x = jimsrand()) < .75)
       mypktptr->payload[0]='Z';   /* corrupt payload */
      else if (x < .875)
       mypktptr->seqnum = 999999;
      else
       mypktptr->acknum = 999999;
    if (TRACE>0)
	printf("          TOLAYER3: packet being corrupted\n");
    }

  if (TRACE>2)
     printf("          TOLAYER3: scheduling arrival on other side\n");
  insertevent(evptr);
}

void tolayer5(int AorB, char datasent[20])
{
  int i;
  if (TRACE>2) {
     printf("          TOLAYER5: data received: ");
     for (i=0; i<20; i++)
        printf("%c",datasent[i]);
     printf("\n");
   }

}