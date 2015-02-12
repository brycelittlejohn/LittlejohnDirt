#ifndef LARLITE_BRYCEDIRTANA_CXX
#define LARLITE_BRYCEDIRTANA_CXX

#include "BryceDirtAna.h"

namespace larlite {

  bool BryceDirtAna::initialize() {

    //
    // This function is called in the beggining of event loop
    // Do all variable initialization you wish to do here.
    // If you have a histogram to fill in the event loop, for example,
    // here is a good place to create one on the heap (i.e. "new TH1D"). 
    //

    //Do some hard-coded defining of the TPC dimensions, and create vectors to hold them.
    TPC_Xmin = 0;
    TPC_Xmax = 256.35;
    TPC_Ymin = -116.5;
    TPC_Ymax = 116.5;
    TPC_Zmin = 0;
    TPC_Zmax = 1036.8;

    top_front_right.SetXYZ(TPC_Ymax,TPC_Zmin,TPC_Xmax);
    top_back_right.SetXYZ(TPC_Ymax,TPC_Zmax,TPC_Xmax);
    top_back_left.SetXYZ(TPC_Ymax,TPC_Zmax,TPC_Xmin);

    bottom_front_right.SetXYZ(TPC_Ymin,TPC_Zmin,TPC_Xmax);
    bottom_back_left.SetXYZ(TPC_Ymin,TPC_Zmax,TPC_Xmin);
    bottom_back_right.SetXYZ(TPC_Ymin,TPC_Zmax,TPC_Xmax);
    bottom_front_left.SetXYZ(TPC_Ymin,TPC_Zmin,TPC_Xmin);

    //FIDUCIAL VOLUME CUTS                                                                                          
    fid = 25; fidz_min = 5; fidz_max = 100;

    //Initialize some vectors.
    ShowerStartPos.Clear();
    ShowerStartDir.Clear();

    TrackStartPos.Clear();
    TrackStartDir.Clear();
    
    ///////////
    //Define analysis tree branche to grab from larlite.
    //////////

    tree = new TTree("tree","");

    tree->Branch("shower_E",&shower_E,"shower_E/D");
    tree->Branch("shower_pdg",&shower_pdg,"shower_pdg/i");

    tree->Branch("shower_birth_ina",&shower_birth_ina,"shower_birth_ina/I");
    tree->Branch("shower_birth_end_ina",&shower_birth_end_ina,"shower_birth_end_ina/I");
    tree->Branch("shower_birth_pdg",&shower_birth_pdg,"shower_birth_pdg/I");
    tree->Branch("shower_mom_pdg",&shower_mom_pdg,"shower_mom_pdg/I");
    tree->Branch("shower_mom_start_ina",&shower_mom_start_ina,"shower_mom_start_ina/I");

    tree->Branch("shower_start_ina",&shower_start_ina,"shower_start_ina/I");
    tree->Branch("shower_start_in_sliver",&shower_start_in_sliver,"shower_start_in_sliver/I");

    tree->Branch("shower_extra_photons",&shower_extra_photons,"shower_extra_photons/I");

    tree->Branch("shower_vertex_Ntrk",&shower_vertex_Ntrk,"shower_vertex_Ntrk/I");
    tree->Branch("shower_vertex_E",&shower_vertex_E,"shower_vertex_E/D");
    tree->Branch("shower_vertex_L",&shower_vertex_L,"shower_vertex_L/D");

    tree->Branch("shower_start_x",&shower_start_x,"shower_start_x/D");
    tree->Branch("shower_start_y",&shower_start_y,"shower_start_y/D");
    tree->Branch("shower_start_z",&shower_start_z,"shower_start_z/D");

    tree->Branch("shower_convert_ina",&shower_convert_ina,"shower_convert_ina/I");
    tree->Branch("shower_convert_inf_5cm_5cm_50cm",&shower_convert_inf_5cm_5cm_50cm,"shower_convert_inf_5cm_5cm_50cm/I");
    tree->Branch("shower_convert_inf_30cm_5cm_50cm",&shower_convert_inf_30cm_5cm_50cm,"shower_convert_inf_30cm_5cm_50cm/I");
    tree->Branch("shower_convert_inf_30cm_25cm_50cm",&shower_convert_inf_30cm_25cm_50cm,"shower_convert_inf_30cm_25cm_50cm/I");

    tree->Branch("shower_convert_inf_30cm_20cm_50cm",&shower_convert_inf_30cm_20cm_50cm,"shower_convert_inf_30cm_20cm_50cm/I");
    tree->Branch("shower_convert_inf_30cm_10cm_50cm",&shower_convert_inf_30cm_10cm_50cm,"shower_convert_inf_30cm_10cm_50cm/I");
    tree->Branch("shower_convert_inf_30cm_15cm_50cm",&shower_convert_inf_30cm_15cm_50cm,"shower_convert_inf_30cm_15cm_50cm/I");

    tree->Branch("shower_convert_x",&shower_convert_x,"shower_convert_x/D");
    tree->Branch("shower_convert_y",&shower_convert_y,"shower_convert_y/D");
    tree->Branch("shower_convert_z",&shower_convert_z,"shower_convert_z/D");

    tree->Branch("shower_multi_enter",&shower_multi_enter,"shower_multi_enter/I");

    tree->Branch("shower_bdw",&shower_bdw,"shower_bdw/D");

    //New Variables, according to Joe.                                                                                                           
    tree->Branch("trk_start_ina",&trk_start_ina,"trk_start_ina/i");
    tree->Branch("trk_pdg",&trk_pdg,"trk_pdg/i");

    tree->Branch("trk_enter",&trk_enter,"trk_enter/i");
    tree->Branch("trk_exit",&trk_exit,"trk_exit/i");

    tree->Branch("nu_pdg",&nu_pdg,"nu_pdg/I");
    tree->Branch("nu_inf",&nu_inf,"nu_inf/I");
    tree->Branch("nu_CC",&nu_CC,"nu_CC/I");

    tree->Branch("nu_int_x",&nu_int_x,"nu_int_x/D");
    tree->Branch("nu_int_y",&nu_int_y,"nu_int_y/D");
    tree->Branch("nu_int_z",&nu_int_z,"nu_int_z/D");


    tree->Branch("nu_neutron",&nu_neutron,"nu_neutron/I");
    tree->Branch("nu_neutron_ina",&nu_neutron_ina,"nu_neutron_ina/I");

    event = 0;

    return true;
  }
  
  void BryceDirtAna::ctr_reset() {
    shower_E=0;
    shower_pdg=0;
    shower_start_ina=0;
    shower_start_in_sliver=0;
    shower_convert_ina=0;
    shower_convert_inf_5cm_5cm_50cm=0;
    shower_convert_inf_30cm_5cm_50cm=0;
    shower_convert_inf_30cm_25cm_50cm=0;
    shower_convert_inf_30cm_20cm_50cm=0;
    shower_convert_inf_30cm_10cm_50cm=0;
    shower_convert_inf_30cm_15cm_50cm=0;

    shower_extra_photons=0;

    shower_birth_ina=0;
    shower_birth_pdg=0;
    shower_mom_pdg=0;
    shower_mom_start_ina=0;

    shower_birth_end_ina=0;

    shower_vertex_Ntrk=0;
    shower_vertex_E=0;
    shower_vertex_L=0;

    shower_bdw=0;

    shower_convert_x = 0;
    shower_convert_y = 0;
    shower_convert_z = 0;

    trk_start_ina=0;
    trk_pdg=0;

    trk_enter=0;
    trk_exit=0;

    nu_int_x=0;
    nu_int_y=0;
    nu_int_z=0;

    nu_pdg = 0;
    nu_inf = 0;
    nu_CC = 0;
    nu_neutron = 0;
    nu_neutron_ina = 0;
    shower_multi_enter = 0;

  }

  bool BryceDirtAna::analyze(storage_manager* storage) {
    
    //
    ////Start by looking at MC truth information
    //
    auto ev_mctruth = storage->get_data<larlite::event_mctruth>("generator");
    if (!ev_mctruth) { std::cout << "FAIL!" << std::endl; return false; }

    for( size_t i = 0; i < ev_mctruth->size(); ++i){

      //
      ////Get true info about neutrino causing event.
      //

      //See if we have a neutrino
      auto neutrino = ev_mctruth->at(i).GetNeutrino();
      if(neutrino.CCNC() == 1){nu_CC = 1;}
      else{nu_CC = 0;}

      //Get PDG and interaction position.
      nu_pdg = neutrino.Nu().PdgCode();
      nu_int_x = neutrino.Nu().Trajectory().at(0).Position().X();
      nu_int_y = neutrino.Nu().Trajectory().at(0).Position().Y();
      nu_int_z = neutrino.Nu().Trajectory().at(0).Position().Z();

      //Determine if neutrino is in fiducial volume or active volume.
      int nu_ina = 0;
      if( neutrino.Nu().Trajectory().at(0).Position().X() > TPC_Xmin &&
          neutrino.Nu().Trajectory().at(0).Position().X() < TPC_Xmax &&
          neutrino.Nu().Trajectory().at(0).Position().Y() > TPC_Ymin &&
          neutrino.Nu().Trajectory().at(0).Position().Y() < TPC_Ymax &&
          neutrino.Nu().Trajectory().at(0).Position().Z() > TPC_Zmin &&
          neutrino.Nu().Trajectory().at(0).Position().Z() < TPC_Zmax)
        nu_ina=1;

      if( neutrino.Nu().Trajectory().at(0).Position().X() > TPC_Xmin+17 &&
          neutrino.Nu().Trajectory().at(0).Position().X() < TPC_Xmax-17 &&
          neutrino.Nu().Trajectory().at(0).Position().Y() > TPC_Ymin+17 &&
          neutrino.Nu().Trajectory().at(0).Position().Y() < TPC_Ymax-17 &&
          neutrino.Nu().Trajectory().at(0).Position().Z() > TPC_Zmin+17 &&
          neutrino.Nu().Trajectory().at(0).Position().Z() < TPC_Zmax-17)
        nu_inf=1;
      else
        nu_inf=0;
      
      //
      ////Get other particle info
      //
      auto part_list = ev_mctruth->at(i).GetParticles();
      int neu_ina = 0;
      int neu = 0;
      int neu_mom = 0;

      //Do this ONLY IF there is no neutrino in the active volume.
      if( part_list.size() != 0 && nu_ina == 0){
	for(int part = 0; part < part_list.size(); part++){
          neu_mom = 0;
	  //IF a particle is a neutron,
          if(part_list.at(part).PdgCode() == 2112){
	    //count it
	    neu++;
	    
	    //is the neutron in the active volume?  BLAH: Why the for loop???
	    for(int k = 0; k < part_list.at(part).Trajectory().size(); k++){
	      
	      if(part_list.at(part).Trajectory().at(k).Position().X() > TPC_Xmin &&
		 part_list.at(part).Trajectory().at(k).Position().X() < TPC_Xmax &&
		 part_list.at(part).Trajectory().at(k).Position().Y() > TPC_Ymin &&
		 part_list.at(part).Trajectory().at(k).Position().Y() < TPC_Ymax &&
		 part_list.at(part).Trajectory().at(k).Position().Z() > TPC_Zmin &&
		 part_list.at(part).Trajectory().at(k).Position().Z() < TPC_Zmax){
		
		neu_ina++;
	      }
	    }
	  }
	}
      }

      if(neu > 0){nu_neutron = 1;}
      else{nu_neutron = 0;}
      
      if(neu_ina > 0){ nu_neutron_ina = 1;}
      else{nu_neutron_ina = 0;}
      
      tree->Fill();
    }

    //
    ////Now move on to looking at the MCShowers and MCTracks.
    //
    
    
    event++;
    std::cout<<"Event number: "<<event<<std::endl;
    
    //
    // Do your event-by-event analysis here. This function is called for 
    // each event in the loop. You have "storage" pointer which contains 
    // event-wise data. To see what is available, check the "Manual.pdf":
    //
    // http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
    // 
    // Or you can refer to Base/DataFormatConstants.hh for available data type
    // enum values. Here is one example of getting PMT waveform collection.
    //
    // event_fifo* my_pmtfifo_v = (event_fifo*)(storage->get_data(DATA::PMFIFO));
    //
    // if( event_fifo )
    //
    //   std::cout << "Event ID: " << my_pmtfifo_v->event_id() << std::endl;
    //
  
    return true;
  }

  bool BryceDirtAna::finalize() {
    if(_fout)
      tree->Write();
    return true;
  }

  //Functions                                                                                                       
  bool BryceDirtAna::IsActive(const TVector3 & startPos){

    if( startPos.X() > TPC_Xmin &&
        startPos.X() < TPC_Xmax &&
        startPos.Y() > TPC_Ymin &&
        startPos.Y() < TPC_Ymax &&
        startPos.Z() > TPC_Zmin &&
        startPos.Z() < TPC_Zmax)
      return true;
    else
      return false;
  }

  bool BryceDirtAna::IsFiducial(const TVector3 & startPos){

    if( startPos.X() > TPC_Xmin+fid &&
        startPos.X() < TPC_Xmax-fid &&
        startPos.Y() > TPC_Ymin+fid &&
        startPos.Y() < TPC_Ymax-fid &&
        startPos.Z() > TPC_Zmin+fidz_min &&
        startPos.Z() < TPC_Zmax-fidz_max)
      return true;
    else
      return false;
  }
  
}
#endif
