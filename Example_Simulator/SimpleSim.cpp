#include "./obj_dir/VSimpleUart.h"
#include "./obj_dir/VSimpleUart__Syms.h"
#include <verilated.h>
#include <verilated_cov.h>
#include <ctime>
#include <cstdlib>

void runSim() {
    VSimpleUart* sim = new VSimpleUart();
    unsigned int cycle_cnt = 0;
    unsigned int main_time = 0;

    sim->reset = 0;
    sim->eval();
    sim->reset = 1;
    sim->eval();
    sim->reset = 0;
    //circuit should be reset
    srand(9831247598);
    //THIS GOES TO DAIKON!
    while (main_time < (unsigned int) ((20 /*# ANT VECTORS*/) * 2)
            && !Verilated::gotFinish()) {
        sim->eval();       //Evaluate model
        main_time++;        //Time passes...

	//set inputs
	//ant->apply_vectors(sim);
	sim->ld_tx_data = rand() % 2;
	sim->tx_data = rand() % 256;
	sim->tx_enable = rand() % 2;

	//rx inputs
	sim->uld_rx_data = rand() % 2;
	sim->rx_enable = rand() % 2;
	sim->rx_in = rand() % 2;
	
	if(main_time % 2 == 0)
	    sim->txclk = ~sim->txclk;

	sim->rxclk = ~sim->rxclk;

	if(sim->txclk){
	    for(int i = 0; i < 24; i++) {
		cout << sim->__VlSymsp->__Vcoverage[i] << " ";
	    }
	    cout << endl;
	}
    }
}

int main(int argc, char* argv[]) {
    runSim();
}
