// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSimpleUart_H_
#define _VSimpleUart_H_

#include "verilated.h"
#include "verilated_cov.h"
class VSimpleUart__Syms;

//----------

VL_MODULE(VSimpleUart) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(reset,0,0);
    VL_IN8(txclk,0,0);
    VL_IN8(rxclk,0,0);
    VL_IN8(ld_tx_data,0,0);
    VL_IN8(tx_data,7,0);
    VL_IN8(tx_enable,0,0);
    VL_OUT8(tx_out,0,0);
    VL_OUT8(tx_empty,0,0);
    VL_IN8(uld_rx_data,0,0);
    VL_OUT8(rx_data,7,0);
    VL_IN8(rx_enable,0,0);
    VL_IN8(rx_in,0,0);
    VL_OUT8(rx_empty,0,0);
    //char	__VpadToAlign13[3];
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__tx_reg,7,0);
    VL_SIG8(v__DOT__tx_cnt,3,0);
    VL_SIG8(v__DOT__rx_reg,7,0);
    VL_SIG8(v__DOT__rx_sample_cnt,3,0);
    VL_SIG8(v__DOT__rx_cnt,3,0);
    VL_SIG8(v__DOT__rx_d1,0,0);
    VL_SIG8(v__DOT__rx_d2,0,0);
    VL_SIG8(v__DOT__rx_busy,0,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vclklast__TOP__reset,0,0);
    VL_SIG8(__Vclklast__TOP__txclk,0,0);
    VL_SIG8(__Vclklast__TOP__rxclk,0,0);
    //char	__VpadToAlign35[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    VSimpleUart__Syms*	__VlSymsp;		// Symbol table
  private:
    // Coverage
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
	const char* hierp, const char* pagep, const char* commentp);
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
  public:
    
    // CONSTRUCTORS
  private:
    VSimpleUart& operator= (const VSimpleUart&);	///< Copying not allowed
    VSimpleUart(const VSimpleUart&);	///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible WRT DPI scope names.
    VSimpleUart(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~VSimpleUart();
    
    // USER METHODS
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VSimpleUart__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VSimpleUart__Syms* symsp, bool first);
  private:
    static QData	_change_request(VSimpleUart__Syms* __restrict vlSymsp);
  public:
    static void	_eval(VSimpleUart__Syms* __restrict vlSymsp);
    static void	_eval_initial(VSimpleUart__Syms* __restrict vlSymsp);
    static void	_eval_settle(VSimpleUart__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__1(VSimpleUart__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__2(VSimpleUart__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
