import HostInterface::*;
import LoopIF::*;

interface Loop;
    interface LoopReq loop;
endinterface

module mkLoop#(
    HostInterface host,
    LoopInd ind
)(Loop);

    interface LoopReq loop;
        method Action req(Bit#(32) x);
            ind.resp(x);
        endmethod
    endinterface
endmodule
