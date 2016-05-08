// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimpleUart.h for the primary calling header

#include "VSimpleUart.h"       // For This
#include "VSimpleUart__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(VSimpleUart) {
    VSimpleUart__Syms* __restrict vlSymsp = __VlSymsp = new VSimpleUart__Syms(this, name());
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    reset = VL_RAND_RESET_I(1);
    txclk = VL_RAND_RESET_I(1);
    ld_tx_data = VL_RAND_RESET_I(1);
    tx_data = VL_RAND_RESET_I(8);
    tx_enable = VL_RAND_RESET_I(1);
    tx_out = VL_RAND_RESET_I(1);
    tx_empty = VL_RAND_RESET_I(1);
    rxclk = VL_RAND_RESET_I(1);
    uld_rx_data = VL_RAND_RESET_I(1);
    rx_data = VL_RAND_RESET_I(8);
    rx_enable = VL_RAND_RESET_I(1);
    rx_in = VL_RAND_RESET_I(1);
    rx_empty = VL_RAND_RESET_I(1);
    v__DOT__tx_reg = VL_RAND_RESET_I(8);
    v__DOT__tx_cnt = VL_RAND_RESET_I(4);
    v__DOT__rx_reg = VL_RAND_RESET_I(8);
    v__DOT__rx_sample_cnt = VL_RAND_RESET_I(4);
    v__DOT__rx_cnt = VL_RAND_RESET_I(4);
    v__DOT__rx_d1 = VL_RAND_RESET_I(1);
    v__DOT__rx_d2 = VL_RAND_RESET_I(1);
    v__DOT__rx_busy = VL_RAND_RESET_I(1);
    __Vclklast__TOP__reset = VL_RAND_RESET_I(1);
    __Vclklast__TOP__txclk = VL_RAND_RESET_I(1);
    __Vclklast__TOP__rxclk = VL_RAND_RESET_I(1);
}

void VSimpleUart::__Vconfigure(VSimpleUart__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    // Coverage Declarations
    __vlCoverInsert(&(vlSymsp->__Vcoverage[0]), first, "SimpleUart.v", 56, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[1]), first, "SimpleUart.v", 72, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "SimpleUart.v", 79, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "SimpleUart.v", 89, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "SimpleUart.v", 94, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "SimpleUart.v", 100, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "SimpleUart.v", 102, 0, ".v", "v_line/uart", "else");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "SimpleUart.v", 97, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "SimpleUart.v", 91, 0, ".v", "v_line/uart", "else");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "SimpleUart.v", 88, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "SimpleUart.v", 85, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "SimpleUart.v", 77, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "SimpleUart.v", 113, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "SimpleUart.v", 67, 0, ".v", "v_line/uart", "else");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "SimpleUart.v", 120, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "SimpleUart.v", 128, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "SimpleUart.v", 130, 0, ".v", "v_line/uart", "else");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "SimpleUart.v", 127, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "SimpleUart.v", 137, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "SimpleUart.v", 140, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "SimpleUart.v", 143, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "SimpleUart.v", 135, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "SimpleUart.v", 149, 0, ".v", "v_line/uart", "if");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "SimpleUart.v", 126, 0, ".v", "v_line/uart", "else");
}

VSimpleUart::~VSimpleUart() {
    delete __VlSymsp; __VlSymsp=NULL;
}

// Coverage
void VSimpleUart::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp) {
    static uint32_t fake_zero_count = 0;
    if (!enable) countp = &fake_zero_count;
    *countp = 0;
    VL_COVER_INSERT(countp,  "filename",filenamep,  "lineno",lineno,  "column",column,
	"hier",string(name())+hierp,  "page",pagep,  "comment",commentp);
}

//--------------------


void VSimpleUart::eval() {
    VSimpleUart__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate VSimpleUart::eval\n"); );
    int __VclockLoop = 0;
    QData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_PRINTF(" Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop < 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void VSimpleUart::_eval_initial_loop(VSimpleUart__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    QData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

VL_INLINE_OPT void VSimpleUart::_sequent__TOP__1(VSimpleUart__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::_sequent__TOP__1\n"); );
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__tx_reg,7,0);
    VL_SIG8(__Vdly__tx_empty,0,0);
    VL_SIG8(__Vdly__v__DOT__tx_cnt,3,0);
    //char	__VpadToAlign7[1];
    // Body
    __Vdly__v__DOT__tx_reg = vlTOPp->v__DOT__tx_reg;
    __Vdly__tx_empty = vlTOPp->tx_empty;
    __Vdly__v__DOT__tx_cnt = vlTOPp->v__DOT__tx_cnt;
    // ALWAYS at SimpleUart.v:119
    if (vlTOPp->reset) {
	++(vlSymsp->__Vcoverage[14]);
	__Vdly__v__DOT__tx_reg = 0U;
	__Vdly__tx_empty = 1U;
	__Vdly__v__DOT__tx_cnt = 0U;
	vlTOPp->tx_out = 1U;
    } else {
	++(vlSymsp->__Vcoverage[23]);
	if (vlTOPp->ld_tx_data) {
	    ++(vlSymsp->__Vcoverage[17]);
	    if (vlTOPp->tx_empty) {
		++(vlSymsp->__Vcoverage[16]);
		__Vdly__v__DOT__tx_reg = vlTOPp->tx_data;
		__Vdly__tx_empty = 0U;
	    } else {
		++(vlSymsp->__Vcoverage[15]);
	    }
	}
	if (((IData)(vlTOPp->tx_enable) & (~ (IData)(vlTOPp->tx_empty)))) {
	    ++(vlSymsp->__Vcoverage[21]);
	    __Vdly__v__DOT__tx_cnt = (0xfU & ((IData)(1U) 
					      + (IData)(vlTOPp->v__DOT__tx_cnt)));
	    if ((0U == (IData)(vlTOPp->v__DOT__tx_cnt))) {
		++(vlSymsp->__Vcoverage[18]);
		vlTOPp->tx_out = 0U;
	    }
	    if (((0U < (IData)(vlTOPp->v__DOT__tx_cnt)) 
		 & (9U > (IData)(vlTOPp->v__DOT__tx_cnt)))) {
		++(vlSymsp->__Vcoverage[19]);
		vlTOPp->tx_out = (1U & ((IData)(vlTOPp->v__DOT__tx_reg) 
					>> (7U & ((IData)(vlTOPp->v__DOT__tx_cnt) 
						  - (IData)(1U)))));
	    }
	    if ((9U == (IData)(vlTOPp->v__DOT__tx_cnt))) {
		++(vlSymsp->__Vcoverage[20]);
		vlTOPp->tx_out = 1U;
		__Vdly__v__DOT__tx_cnt = 0U;
		__Vdly__tx_empty = 1U;
	    }
	}
	if ((1U & (~ (IData)(vlTOPp->tx_enable)))) {
	    ++(vlSymsp->__Vcoverage[22]);
	    __Vdly__v__DOT__tx_cnt = 0U;
	}
    }
    vlTOPp->tx_empty = __Vdly__tx_empty;
    vlTOPp->v__DOT__tx_cnt = __Vdly__v__DOT__tx_cnt;
    vlTOPp->v__DOT__tx_reg = __Vdly__v__DOT__tx_reg;
}

VL_INLINE_OPT void VSimpleUart::_sequent__TOP__2(VSimpleUart__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::_sequent__TOP__2\n"); );
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__rx_reg,7,0);
    VL_SIG8(__Vdly__v__DOT__rx_sample_cnt,3,0);
    VL_SIG8(__Vdly__v__DOT__rx_cnt,3,0);
    VL_SIG8(__Vdly__v__DOT__rx_d1,0,0);
    VL_SIG8(__Vdly__v__DOT__rx_d2,0,0);
    VL_SIG8(__Vdly__v__DOT__rx_busy,0,0);
    //char	__VpadToAlign34[2];
    // Body
    __Vdly__v__DOT__rx_reg = vlTOPp->v__DOT__rx_reg;
    __Vdly__v__DOT__rx_sample_cnt = vlTOPp->v__DOT__rx_sample_cnt;
    __Vdly__v__DOT__rx_cnt = vlTOPp->v__DOT__rx_cnt;
    __Vdly__v__DOT__rx_d1 = vlTOPp->v__DOT__rx_d1;
    __Vdly__v__DOT__rx_d2 = vlTOPp->v__DOT__rx_d2;
    __Vdly__v__DOT__rx_busy = vlTOPp->v__DOT__rx_busy;
    // ALWAYS at SimpleUart.v:55
    if (vlTOPp->reset) {
	++(vlSymsp->__Vcoverage[0]);
	__Vdly__v__DOT__rx_reg = 0U;
	vlTOPp->rx_data = 0U;
	__Vdly__v__DOT__rx_sample_cnt = 0U;
	__Vdly__v__DOT__rx_cnt = 0U;
	__Vdly__v__DOT__rx_d1 = 1U;
	__Vdly__v__DOT__rx_d2 = 1U;
	__Vdly__v__DOT__rx_busy = 0U;
	vlTOPp->rx_empty = 1U;
    } else {
	++(vlSymsp->__Vcoverage[13]);
	__Vdly__v__DOT__rx_d1 = vlTOPp->rx_in;
	if (vlTOPp->uld_rx_data) {
	    ++(vlSymsp->__Vcoverage[1]);
	    vlTOPp->rx_data = vlTOPp->v__DOT__rx_reg;
	    vlTOPp->rx_empty = 1U;
	}
	if (vlTOPp->rx_enable) {
	    ++(vlSymsp->__Vcoverage[11]);
	    if ((1U & ((~ (IData)(vlTOPp->v__DOT__rx_busy)) 
		       & (~ (IData)(vlTOPp->v__DOT__rx_d2))))) {
		++(vlSymsp->__Vcoverage[2]);
		__Vdly__v__DOT__rx_busy = 1U;
		__Vdly__v__DOT__rx_sample_cnt = 1U;
		__Vdly__v__DOT__rx_cnt = 0U;
	    }
	    if (vlTOPp->v__DOT__rx_busy) {
		__Vdly__v__DOT__rx_sample_cnt = (0xfU 
						 & ((IData)(1U) 
						    + (IData)(vlTOPp->v__DOT__rx_sample_cnt)));
		++(vlSymsp->__Vcoverage[10]);
		if ((7U == (IData)(vlTOPp->v__DOT__rx_sample_cnt))) {
		    ++(vlSymsp->__Vcoverage[9]);
		    if (((IData)(vlTOPp->v__DOT__rx_d2) 
			 & (0U == (IData)(vlTOPp->v__DOT__rx_cnt)))) {
			++(vlSymsp->__Vcoverage[3]);
			__Vdly__v__DOT__rx_busy = 0U;
		    } else {
			__Vdly__v__DOT__rx_cnt = (0xfU 
						  & ((IData)(1U) 
						     + (IData)(vlTOPp->v__DOT__rx_cnt)));
			++(vlSymsp->__Vcoverage[8]);
			if (((0U < (IData)(vlTOPp->v__DOT__rx_cnt)) 
			     & (9U > (IData)(vlTOPp->v__DOT__rx_cnt)))) {
			    ++(vlSymsp->__Vcoverage[4]);
			    __Vdly__v__DOT__rx_reg 
				= (((~ ((IData)(1U) 
					<< (7U & ((IData)(vlTOPp->v__DOT__rx_cnt) 
						  - (IData)(1U))))) 
				    & (IData)(__Vdly__v__DOT__rx_reg)) 
				   | ((IData)(vlTOPp->v__DOT__rx_d2) 
				      << (7U & ((IData)(vlTOPp->v__DOT__rx_cnt) 
						- (IData)(1U)))));
			}
			if ((9U == (IData)(vlTOPp->v__DOT__rx_cnt))) {
			    ++(vlSymsp->__Vcoverage[7]);
			    __Vdly__v__DOT__rx_busy = 0U;
			    if (vlTOPp->v__DOT__rx_d2) {
				++(vlSymsp->__Vcoverage[6]);
				vlTOPp->rx_empty = 0U;
			    } else {
				++(vlSymsp->__Vcoverage[5]);
			    }
			}
		    }
		}
	    }
	}
	if ((1U & (~ (IData)(vlTOPp->rx_enable)))) {
	    ++(vlSymsp->__Vcoverage[12]);
	    __Vdly__v__DOT__rx_busy = 0U;
	}
	__Vdly__v__DOT__rx_d2 = vlTOPp->v__DOT__rx_d1;
    }
    vlTOPp->v__DOT__rx_reg = __Vdly__v__DOT__rx_reg;
    vlTOPp->v__DOT__rx_busy = __Vdly__v__DOT__rx_busy;
    vlTOPp->v__DOT__rx_d2 = __Vdly__v__DOT__rx_d2;
    vlTOPp->v__DOT__rx_sample_cnt = __Vdly__v__DOT__rx_sample_cnt;
    vlTOPp->v__DOT__rx_cnt = __Vdly__v__DOT__rx_cnt;
    vlTOPp->v__DOT__rx_d1 = __Vdly__v__DOT__rx_d1;
}

void VSimpleUart::_eval(VSimpleUart__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::_eval\n"); );
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->reset) & (~ (IData)(vlTOPp->__Vclklast__TOP__reset))) 
	 | ((IData)(vlTOPp->txclk) & (~ (IData)(vlTOPp->__Vclklast__TOP__txclk))))) {
	vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    if ((((IData)(vlTOPp->reset) & (~ (IData)(vlTOPp->__Vclklast__TOP__reset))) 
	 | ((IData)(vlTOPp->rxclk) & (~ (IData)(vlTOPp->__Vclklast__TOP__rxclk))))) {
	vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__reset = vlTOPp->reset;
    vlTOPp->__Vclklast__TOP__txclk = vlTOPp->txclk;
    vlTOPp->__Vclklast__TOP__rxclk = vlTOPp->rxclk;
}

void VSimpleUart::_eval_initial(VSimpleUart__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::_eval_initial\n"); );
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VSimpleUart::final() {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::final\n"); );
    // Variables
    VSimpleUart__Syms* __restrict vlSymsp = this->__VlSymsp;
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VSimpleUart::_eval_settle(VSimpleUart__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::_eval_settle\n"); );
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

VL_INLINE_OPT QData VSimpleUart::_change_request(VSimpleUart__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VSimpleUart::_change_request\n"); );
    VSimpleUart* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}
