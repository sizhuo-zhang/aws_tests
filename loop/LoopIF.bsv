
interface LoopReq;
    method Action req(Bit#(32) x);
endinterface

interface LoopInd;
    method Action resp(Bit#(32) x);
endinterface
