typedef Sarray<int,  26> int26;
typedef Sarray<int,  27> int27;
typedef Sarray<int*, 26> intp26;
typedef Sarray<Particle*, 26> Particlep26;

struct TicketCom {
    MPI_Request sendreq[26], sendcellsreq[26], sendcountreq[26];
    MPI_Request recvreq[26], recvcellsreq[26], recvcountreq[26];
    int recv_tags[26], recv_counts[26], dstranks[26];
};

struct Ticketrnd {
    
};

struct TicketShalo {
    
};

struct TicketRhalo {
    
};
