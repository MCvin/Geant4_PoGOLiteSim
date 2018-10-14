//
//  StructureConstruction.cc 2014-12-09  Maxime Chauvin
//
//  Includes the PVA, RFA, Neutron shield, STM, STR and AMU
//  based on Merlin Kole 2014-7 updated by Maxime Chauvin 2014-12-09
//

#include "StructureConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

StructureConstruction::StructureConstruction(G4LogicalVolume* l_Pogo, G4LogicalVolume* l_Polarimeter)
{
  // define some rotation matrices
  DefineRotations();

  // Elements
  G4Element *elementH = new G4Element("Hydrogen", "H",  1.,  1.0079*g/mole);
  G4Element *elementC = new G4Element("Carbon",   "C",  6.,  12.011*g/mole);

  G4NistManager * nist_manager = G4NistManager::Instance();
  G4Material * air_3hPa = nist_manager->BuildMaterialWithNewDensity("air_3hPa","G4_AIR", 0.0041*kg/m3);
  G4Material * Al = nist_manager->FindOrBuildMaterial("G4_Al");
  G4Material * PE = nist_manager->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material * Glass = nist_manager->FindOrBuildMaterial("G4_GLASS_PLATE");
  G4Material * PVC = nist_manager->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  G4Material * Mylar = nist_manager->FindOrBuildMaterial("G4_MYLAR");					// also use for PEEK wich is similar
  G4Material * PVDF = nist_manager->FindOrBuildMaterial("G4_POLYVINYLIDENE_FLUORIDE");	// close to PVF (Tedlar)
  
  //Epoxy (for FR4)
  G4Material* Epoxy = new G4Material("Epoxy", 1.2*g/cm3, 2);
  Epoxy->AddElement(elementH, 2);
  Epoxy->AddElement(elementC, 2);
  //FR4 (Glass + Epoxy)
  G4Material * SiO2 = nist_manager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material* FR4 = new G4Material("FR4", 1.86*g/cm3, 2);
  FR4->AddMaterial(SiO2, 0.528);
  FR4->AddMaterial(Epoxy, 0.472);


  ////////////////////////////////// Top pressure vessel //////////////////////////////////////////

  //// Top Pressure Vessel
  const G4String TopPVname = "Top_PV";
  G4Tubs* s_Top_PV = new G4Tubs(TopPVname, 427.0/2.0*mm, 433.0/2.0*mm, 868/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Top_PV = new G4LogicalVolume(s_Top_PV, Al, TopPVname);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,384.5*mm), l_Top_PV, TopPVname, l_Polarimeter, false, 0);

  //// Top Plate
  const G4String TopPlatename = "Top_Plate";
  G4Tubs* s_Top_plate = new G4Tubs(TopPlatename, 280.0/2.0*mm, 427.0/2.0*mm, 25.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Top_plate = new G4LogicalVolume(s_Top_plate, Al, TopPlatename);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,806.0*mm), l_Top_plate, TopPlatename, l_Polarimeter, false, 0);

  //// Mylar + Tedlar + PEEK window
  G4Tubs* s_Mylar = new G4Tubs("Mylar_Window", 0.0*mm, 320.0/2.0*mm, 0.2/2.0*mm, 0.*deg, 360.*deg);
  G4Tubs* s_Tedlar = new G4Tubs("Tedlar_Window", 0.0*mm, 320.0/2.0*mm, 0.12/2.0*mm, 0.*deg, 360.*deg);
  G4Tubs* s_PEEK = new G4Tubs("PEEK_Window", 0.0*mm, 320.0/2.0*mm, 0.19/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Mylar = new G4LogicalVolume(s_Mylar, Mylar, "Mylar_Window");
  G4LogicalVolume* l_Tedlar = new G4LogicalVolume(s_Tedlar, PVDF, "Tedlar_Window");
  G4LogicalVolume* l_PEEK = new G4LogicalVolume(s_PEEK, Mylar, "PEEK_Window");
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,818.910*mm),  l_Mylar,  "Mylar_Window", l_Polarimeter, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,818.750*mm), l_Tedlar, "Tedlar_Window", l_Polarimeter, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,818.595*mm),   l_PEEK,   "PEEK_Window", l_Polarimeter, false, 0);

  //// Base Plate
  const G4String BasePlatename = "Base_Plate";
  G4Tubs* s_Base_plate = new G4Tubs(BasePlatename, 201.0*mm, 427.0/2.0*mm, 20.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Base_plate = new G4LogicalVolume(s_Base_plate, Al, BasePlatename);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-39.5*mm), l_Base_plate, BasePlatename, l_Polarimeter, false, 0);	       

  ////////////////////////////////// PMT pressure vessel //////////////////////////////////////////

  //// PMT PV
  const G4String PMT_PV_name = "PMT_PV";
  G4Tubs* s_PMT_PV = new G4Tubs(PMT_PV_name, 191*mm, 201.0*mm, 400.0/2*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_PMT_PV = new G4LogicalVolume(s_PMT_PV, Al, PMT_PV_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-249.5*mm), l_PMT_PV, PMT_PV_name, l_Polarimeter, false, 0);

  //// Cold plate
  const G4String Cold_plate_name = "Cold_plate";
  G4Tubs* s_Cold_plate = new G4Tubs(Cold_plate_name, 0.0*mm, 190.0*mm, 10.0/2*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Cold_plate = new G4LogicalVolume(s_Cold_plate, Al, Cold_plate_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-320.0*mm), l_Cold_plate, Cold_plate_name, l_Polarimeter, false, 0);

  //// Bottom Poly shield
  const G4String n_Bottom_poly = "Bottom poly block";
  G4Tubs* s_Bottom_poly = new G4Tubs(n_Bottom_poly, 0.0*mm, 190.0*mm, 75.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Bottom_poly = new G4LogicalVolume(s_Bottom_poly, PE, n_Bottom_poly);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-450.0*mm), l_Bottom_poly, n_Bottom_poly, l_Polarimeter, false, 0);

  ////////////////////////////////// Electronics pressure vessel //////////////////////////////////////////

  //// El_PV 
  const G4String ElPVname = "El_PV";
  G4Tubs* s_El_PV = new G4Tubs(ElPVname, 191.0*mm, 201.0*mm, 400.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_El_PV = new G4LogicalVolume(s_El_PV, Al, ElPVname);
  new G4PVPlacement(0, G4ThreeVector(0.*cm,0.*cm,-649.5*mm), l_El_PV, ElPVname, l_Polarimeter, false, 0);

  //// El_bottom 
  const G4String Elbottomname = "El_Bottom";
  G4Tubs* s_El_bottom = new G4Tubs(Elbottomname, 0.0*mm, 435.0/2.0*mm, 17.5*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_El_bottom = new G4LogicalVolume(s_El_bottom, Al, Elbottomname);
  new G4PVPlacement(0, G4ThreeVector(0.*cm,0.*cm,-867.0*mm), l_El_bottom, Elbottomname, l_Polarimeter, false, 0);

  //// FADC boards
  const G4String FADCname = "FADC boards";
  G4Box* s_FADC = new G4Box("FADCname", 130./2.0*mm, 15./2.0*mm, 170./2.0*mm);
  G4LogicalVolume* l_FADC = new G4LogicalVolume(s_FADC, FR4, FADCname);
  // place 16 copies of FADC board (12 FADC + DIO + IUB + 2 routers)
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm,  10.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 1);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm,  30.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 2);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm,  50.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 3);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm,  70.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 4);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm,  90.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 5);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm, 110.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 6);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm, -10.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 7);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm, -30.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 8);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm, -50.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 9);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm, -70.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 10);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm, -90.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 11);
  new G4PVPlacement(     0, G4ThreeVector(-20.0*mm,-110.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 12);
  new G4PVPlacement(zRot90, G4ThreeVector( 55.0*mm,  70.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 13);
  new G4PVPlacement(zRot90, G4ThreeVector( 75.0*mm,  70.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 14);
  new G4PVPlacement(zRot90, G4ThreeVector( 55.0*mm, -70.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 15);
  new G4PVPlacement(zRot90, G4ThreeVector( 75.0*mm, -70.0*mm,-700.0*mm), l_FADC, FADCname, l_Polarimeter, false, 16);

  //// Add other stuff here, the electronic is closely packed stuff

  ////////////////////////////////////////// RFA and neutron shield /////////////////////////////////

  //// RFA mother volume
  const G4String RFAmom = "RFA_mother";
  G4Tubs* s_RFA_mom = new G4Tubs(RFAmom, 233.5*mm, 400.0*mm, 1262.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_RFA_mom = new G4LogicalVolume(s_RFA_mom, air_3hPa, RFAmom);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), l_RFA_mom, RFAmom, l_Pogo, false, 0);

  //// RFA 
  const G4String RFAname = "RFA";
  G4Tubs* s_RFA = new G4Tubs(RFAname, 233.5*mm, 238.5*mm, 1262.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_RFA = new G4LogicalVolume(s_RFA, Al, RFAname);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,0.0*cm), l_RFA, RFAname, l_RFA_mom, false, 0);

  //// Thick Flange
  const G4String Flange_name1 = "Flange_thick";
  G4Tubs* s_Flange1 = new G4Tubs(Flange_name1, 233.5*mm, 338.5*mm, 7.5*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Flange1 = new G4LogicalVolume(s_Flange1, Al, Flange_name1);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm, 623.5*mm), l_Flange1, Flange_name1, l_RFA_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-623.5*mm), l_Flange1, Flange_name1, l_RFA_mom, false, 1);

  //// Thin Flanges
  const G4String Flange_name2 = "Flange_thin";
  G4Tubs* s_Flange2 = new G4Tubs(Flange_name2, 233.5*mm, 338.5*mm, 2.5*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_Flange2 = new G4LogicalVolume(s_Flange2, Al, Flange_name2);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm, 318.5*mm), l_Flange2, Flange_name2, l_RFA_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,  18.5*mm), l_Flange2, Flange_name2, l_RFA_mom, false, 1);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-136.5*mm), l_Flange2, Flange_name2, l_RFA_mom, false, 2);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,-377.5*mm), l_Flange2, Flange_name2, l_RFA_mom, false, 3);

  //// Poly blocks
  const G4String Poly10_name1 = "Poly_block10";
  G4Tubs* s_Poly10_1 = new G4Tubs(Poly10_name1, 238.5*mm, 338.5*mm, 117.5*mm, 0.5*deg, 44.0*deg);
  G4LogicalVolume* l_Poly10_1 = new G4LogicalVolume(s_Poly10_1, PE, Poly10_name1);
  new G4PVPlacement(      0, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 0);
  new G4PVPlacement( zRot45, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 1);
  new G4PVPlacement( zRot90, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 2);
  new G4PVPlacement(zRot135, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 3);
  new G4PVPlacement(zRot180, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 4);
  new G4PVPlacement(zRot225, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 5);
  new G4PVPlacement(zRot270, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 6);
  new G4PVPlacement(zRot315, G4ThreeVector(0.0*cm,0.0*cm,198.5*mm), l_Poly10_1, Poly10_name1, l_RFA_mom, false, 7);

  const G4String Poly15_name1 = "Poly_block15_1";
  G4Tubs* s_Poly15_1 = new G4Tubs(Poly15_name1, 238.5*mm, 388.5*mm, 30.0*mm, 0.5*deg, 44.0*deg);
  G4LogicalVolume* l_Poly15_1 = new G4LogicalVolume(s_Poly15_1, PE, Poly15_name1);
  new G4PVPlacement(      0, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 0);
  new G4PVPlacement( zRot45, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 1);
  new G4PVPlacement( zRot90, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 2);
  new G4PVPlacement(zRot135, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 3);
  new G4PVPlacement(zRot180, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 4);
  new G4PVPlacement(zRot225, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 5);
  new G4PVPlacement(zRot270, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 6);
  new G4PVPlacement(zRot315, G4ThreeVector(0.0*cm,0.0*cm,51.0*mm), l_Poly15_1, Poly15_name1, l_RFA_mom, false, 7);

  const G4String Poly15_name2 = "Poly_block15_2";
  G4Tubs* s_Poly15_2 = new G4Tubs(Poly15_name2, 238.5*mm, 388.5*mm, 75.0*mm, 0.5*deg, 44.0*deg);
  G4LogicalVolume* l_Poly15_2 = new G4LogicalVolume(s_Poly15_2, PE, Poly15_name2);
  new G4PVPlacement(      0, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 0);
  new G4PVPlacement( zRot45, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 1);
  new G4PVPlacement( zRot90, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 2);
  new G4PVPlacement(zRot135, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 3);
  new G4PVPlacement(zRot180, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 4);
  new G4PVPlacement(zRot225, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 5);
  new G4PVPlacement(zRot270, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 6);
  new G4PVPlacement(zRot315, G4ThreeVector(0.0*cm,0.0*cm,-59.0*mm), l_Poly15_2, Poly15_name2, l_RFA_mom, false, 7);

  const G4String Poly15_name3 = "Poly_block15_3";
  G4Tubs* s_Poly15_3 = new G4Tubs(Poly15_name3, 238.5*mm, 388.5*mm, 70.0*mm, 0.5*deg, 44.0*deg);
  G4LogicalVolume* l_Poly15_3 = new G4LogicalVolume(s_Poly15_3, PE, Poly15_name3);
  new G4PVPlacement(      0, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 0);
  new G4PVPlacement( zRot45, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 1);
  new G4PVPlacement( zRot90, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 2);
  new G4PVPlacement(zRot135, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 3);
  new G4PVPlacement(zRot180, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 4);
  new G4PVPlacement(zRot225, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 5);
  new G4PVPlacement(zRot270, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 6);
  new G4PVPlacement(zRot315, G4ThreeVector(0.0*cm,0.0*cm,-209.0*mm), l_Poly15_3, Poly15_name3, l_RFA_mom, false, 7);

  const G4String Poly10_name2 = "Poly_block10_2";
  G4Tubs* s_Poly10_2 = new G4Tubs(Poly10_name2, 238.5*mm, 338.5*mm, 47.5*mm, 0.5*deg, 44.0*deg);
  G4LogicalVolume* l_Poly10_2 = new G4LogicalVolume(s_Poly10_2, PE, Poly10_name2);
  new G4PVPlacement(      0, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 0);
  new G4PVPlacement( zRot45, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 1);
  new G4PVPlacement( zRot90, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 2);
  new G4PVPlacement(zRot135, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 3);
  new G4PVPlacement(zRot180, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 4);
  new G4PVPlacement(zRot225, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 5);
  new G4PVPlacement(zRot270, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 6);
  new G4PVPlacement(zRot315, G4ThreeVector(0.0*cm,0.0*cm,-327.5*mm), l_Poly10_2, Poly10_name2, l_RFA_mom, false, 7);

  const G4String Poly10_name3 = "Poly_block10_3";
  G4Tubs* s_Poly10_3 = new G4Tubs(Poly10_name3, 238.5*mm, 338.5*mm, 67.5*mm, 0.5*deg, 44.0*deg);
  G4LogicalVolume* l_Poly10_3 = new G4LogicalVolume(s_Poly10_3, PE, Poly10_name3);
  new G4PVPlacement(      0, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 0);
  new G4PVPlacement( zRot45, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 1);
  new G4PVPlacement( zRot90, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 2);
  new G4PVPlacement(zRot135, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 3);
  new G4PVPlacement(zRot180, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 4);
  new G4PVPlacement(zRot225, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 5);
  new G4PVPlacement(zRot270, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 6);
  new G4PVPlacement(zRot315, G4ThreeVector(0.0*mm,0.0*mm,-447.5*mm), l_Poly10_3, Poly10_name3, l_RFA_mom, false, 7);


  //////////////////////////////////// STM //////////////////////////////////////////////////////////////////////////////////////////

  //// STM_mother
  const G4String STMname = "STM_mother";
  G4Tubs* s_STM_mom = new G4Tubs(STMname, 0.0*mm, 122.0*mm, 1544.21/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_mom = new G4LogicalVolume(s_STM_mom, air_3hPa, STMname);
  new G4PVPlacement(0, G4ThreeVector(-374.1*mm,-374.1*mm,120.0*mm), l_STM_mom, STMname, l_Pogo, false, 0);

  //// STM baffle
  const G4String Bafflename = "STM baffle";
  G4Tubs* s_STM_baffle = new G4Tubs(Bafflename, 220.0/2.0*mm, 225.0/2.0*mm, 913.21/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_baffle = new G4LogicalVolume(s_STM_baffle, FR4, Bafflename);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,310.5*mm), l_STM_baffle, Bafflename, l_STM_mom, false, 0);

  //// STM_baffle plate 1
  const G4String STM_baffle_name1 = "baffle_plate_1";
  G4Tubs* s_STM_baffle_plate1 = new G4Tubs(STM_baffle_name1, 194.0/2.0*mm, 220.0/2.0*mm, 4.8/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_baffle_plate1 = new G4LogicalVolume(s_STM_baffle_plate1, Al, STM_baffle_name1);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,762.205*mm), l_STM_baffle_plate1, STM_baffle_name1, l_STM_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,662.205*mm), l_STM_baffle_plate1, STM_baffle_name1, l_STM_mom, false, 1);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,562.205*mm), l_STM_baffle_plate1, STM_baffle_name1, l_STM_mom, false, 2);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,462.205*mm), l_STM_baffle_plate1, STM_baffle_name1, l_STM_mom, false, 3);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,362.205*mm), l_STM_baffle_plate1, STM_baffle_name1, l_STM_mom, false, 4);

  //// STM_baffle plate 2
  const G4String STM_baffle_name2 = "baffle_plate_2";
  G4Tubs* s_STM_baffle_plate2 = new G4Tubs(STM_baffle_name2, 160.0/2.0*mm, 220.0/2.0*mm, 4.8/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_baffle_plate2 = new G4LogicalVolume(s_STM_baffle_plate2, Al, STM_baffle_name2);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm, 262.205*mm), l_STM_baffle_plate2, STM_baffle_name2, l_STM_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm, 162.205*mm), l_STM_baffle_plate2, STM_baffle_name2, l_STM_mom, false, 1);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,  62.205*mm), l_STM_baffle_plate2, STM_baffle_name2, l_STM_mom, false, 2);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm, -38.795*mm), l_STM_baffle_plate2, STM_baffle_name2, l_STM_mom, false, 3);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,-138.795*mm), l_STM_baffle_plate2, STM_baffle_name2, l_STM_mom, false, 4);

  //// STM 
  const G4String STM_name = "STM";
  G4Tubs* s_STM = new G4Tubs(STM_name, 184.5/2.0*mm, 189.5/2.0*mm, 600.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM = new G4LogicalVolume(s_STM, Al, STM_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,-456.7*mm), l_STM, STM_name, l_STM_mom, false, 0);

  //// STM_centre
  const G4String STM_centre_name = "STM_centre";
  G4Tubs* s_STM_centre = new G4Tubs(STM_centre_name, 0*mm, 75.0/2.0*mm, 590.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_centre = new G4LogicalVolume(s_STM_centre, FR4, STM_centre_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,-456.7*mm), l_STM_centre, STM_centre_name, l_STM_mom, false, 0);

  //// STM_bottom_plate
  const G4String STM_bottom_name = "STM_bottom";
  G4Tubs* s_STM_bottom = new G4Tubs(STM_bottom_name, 0.0*mm, 121.375*mm, 10.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_bottom = new G4LogicalVolume(s_STM_bottom, Al, STM_bottom_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,-762.105*mm), l_STM_bottom, STM_bottom_name, l_STM_mom, false, 0);

  //// STM_top_plate
  const G4String STM_top_name = "STM_top";
  G4Tubs* s_STM_top = new G4Tubs(STM_top_name, 184.5/2.0*mm, 121.375*mm, 10.0/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_top = new G4LogicalVolume(s_STM_top, Al, STM_top_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,-151.205*mm), l_STM_top, STM_top_name, l_STM_mom, false, 0);

  //// STM_window
  const G4String STM_window_name = "STM_window";
  G4Tubs* s_STM_window = new G4Tubs(STM_window_name, 0*mm, 184.5/2.0*mm, 7.5/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STM_window = new G4LogicalVolume(s_STM_window, Glass, STM_window_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*mm,-151.205*mm), l_STM_window, STM_window_name, l_STM_mom, false, 0);

  ///////////////////////////////////// STR /////////////////////////////////////////////////////////////

  //// STR_mother
  const G4String STRname = "STR_mother";
  G4Tubs* s_STR_mom = new G4Tubs(STRname, 0.0*mm, 140.0/2.0*mm, 920/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_mom = new G4LogicalVolume(s_STR_mom, air_3hPa, STRname);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,-489*mm,380.0*mm), l_STR_mom, STRname, l_Pogo, false, 0);

  const G4String STR_baffle_name = "STR_baffle";
  G4Tubs* s_STR_baffle = new G4Tubs(STR_baffle_name, 135.0/2.0*mm, 140.0/2.0*mm, 510/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_baffle = new G4LogicalVolume(s_STR_baffle, PVC, STR_baffle_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm,205.0*mm), l_STR_baffle, STR_baffle_name, l_STR_mom, false, 0);

  const G4String STR_plate_name = "STR_baffle_plate";
  G4Tubs* s_STR_baffle_plate = new G4Tubs(STR_plate_name, 105.0/2.0*mm, 135.0/2.0*mm, 4.8/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_baffle_plate = new G4LogicalVolume(s_STR_baffle_plate, Al, STR_plate_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,455.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,395.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 1);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,345.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 2);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,295.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 3);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,245.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 4);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,195.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 5);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,145.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 6);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm, 95.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 7);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm, 45.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 8);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm, -5.0*mm), l_STR_baffle_plate, STR_plate_name, l_STR_mom, false, 9);

  const G4String STR_name = "STR";
  G4Tubs* s_STR = new G4Tubs(STR_name, 92.0/2.0*mm, 97.0/2.0*mm, 390/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR = new G4LogicalVolume(s_STR, Al, STR_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm,-255.0*mm), l_STR, STR_name, l_STR_mom, false, 0);

  const G4String STR_bottom_name = "STR_bottom";
  G4Tubs* s_STR_bottom = new G4Tubs(STR_bottom_name, 0.0*mm, 97.0/2.0*mm, 10/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_bottom = new G4LogicalVolume(s_STR_bottom, Al, STR_bottom_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm,-455.0*mm), l_STR_bottom, STR_bottom_name, l_STR_mom, false, 0);

  const G4String STR_top_name = "STR_top";
  G4Tubs* s_STR_top = new G4Tubs(STR_top_name, 97.0/2*mm, 140.0/2.0*mm, 10/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_top = new G4LogicalVolume(s_STR_top, Al, STR_top_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm,-55.0*mm), l_STR_top, STR_top_name, l_STR_mom, false, 0);

  const G4String STR_window_name = "STR_window";
  G4Tubs* s_STR_window = new G4Tubs(STR_top_name, 0.0*mm, 97.0/2.0*mm, 7.5/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_window = new G4LogicalVolume(s_STR_window, Glass, STR_window_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm,-55.0*mm), l_STR_window, STR_window_name, l_STR_mom, false, 0);

  const G4String STR_centre_name = "STR_centre";
  G4Tubs* s_STR_centre = new G4Tubs(STR_centre_name, 0.0*mm, 75.0/2.0*mm, 380/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_STR_centre = new G4LogicalVolume(s_STR_centre, FR4, STR_centre_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm,-255.0*mm), l_STR_centre, STR_centre_name, l_STR_mom, false, 0);


  ///////////////////////////////////// AMU /////////////////////////////////////////////////////////////

  //// AMU_mother
  const G4String AMUname = "AMU_mother";
  G4Tubs* s_AMU_mom = new G4Tubs(AMUname, 0.0*mm, 190.0/2.0*mm, 1000/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_AMU_mom = new G4LogicalVolume(s_AMU_mom, air_3hPa, AMUname);
  new G4PVPlacement(0, G4ThreeVector(374.1*mm,-374.1*mm,420.0*mm), l_AMU_mom, AMUname, l_Pogo, false, 0);

  //// AMU
  const G4String AMU_name = "AMU";
  G4Tubs* s_AMU = new G4Tubs(AMU_name, 180.0/2.0*mm, 190.0/2.0*mm, 580/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_AMU = new G4LogicalVolume(s_AMU, Al, AMU_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,-200.0*mm), l_AMU, AMU_name, l_AMU_mom, false, 0);

  //// AMU_centre
  const G4String AMU_centre_name = "AMU_centre";
  G4Tubs* s_AMU_centre = new G4Tubs(AMU_centre_name, 0.0*mm, 100.0/2.0*mm, 580/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_AMU_centre = new G4LogicalVolume(s_AMU_centre, FR4, AMU_centre_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,-200.0*mm), l_AMU_centre, AMU_centre_name, l_AMU_mom, false, 0);

  //// AMU_top
  const G4String AMU_top_name = "AMU_top";
  G4Tubs* s_AMU_top = new G4Tubs(AMU_top_name, 0.0*mm, 190.0/2.0*mm, 10/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_AMU_top = new G4LogicalVolume(s_AMU_top, Al, AMU_top_name);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,  95.0*mm), l_AMU_top, AMU_top_name, l_AMU_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm,0.0*mm,-495.0*mm), l_AMU_top, AMU_top_name, l_AMU_mom, false, 0);

  //// AMU_baffle
  const G4String AMU_baffle_name = "AMU_baffle";
  G4Tubs* s_AMU_baffle = new G4Tubs(AMU_baffle_name, 75.0/2.0*mm, 80.0/2.0*mm, 400/2.0*mm, 0.*deg, 360.*deg);
  G4LogicalVolume* l_AMU_baffle = new G4LogicalVolume(s_AMU_baffle, PVC, AMU_baffle_name);
  new G4PVPlacement(0, G4ThreeVector(-90.0/2.0*mm,0.0*mm,300.0*mm), l_AMU_baffle, AMU_baffle_name, l_AMU_mom, false, 0);
  new G4PVPlacement(0, G4ThreeVector( 90.0/2.0*mm,0.0*mm,300.0*mm), l_AMU_baffle, AMU_baffle_name, l_AMU_mom, false, 1);


  ///////////////////////////////////// Visualization ///////////////////////////////////////////////////
  G4VisAttributes* colourWhite = new G4VisAttributes(G4Colour(1.,1.,1.));
  G4VisAttributes* colourDirtyWhite = new G4VisAttributes(G4Colour(1.,1.,0.8));
  G4VisAttributes* colourGreen = new G4VisAttributes(G4Colour(0.,1.,0.));
  G4VisAttributes* colourBlue = new G4VisAttributes(G4Colour(0.,0.,1.));
  G4VisAttributes* colourLightBlue = new G4VisAttributes(G4Colour(0.6,0.6,1.));
  G4VisAttributes* colourLighterBlue = new G4VisAttributes(G4Colour(0.8,0.8,1.));
  G4VisAttributes* colourRed = new G4VisAttributes(G4Colour(1.0,0.4,0.4));
  G4VisAttributes* colourGrey = new G4VisAttributes(G4Colour(0.8,0.8,0.8));
  G4VisAttributes* colourDark = new G4VisAttributes(G4Colour(0.2,0.2,0.2));
  G4VisAttributes* colourVeryDark = new G4VisAttributes(G4Colour(0.1,0.1,0.1,0.1));
  G4VisAttributes* colourDirtyYellow = new G4VisAttributes(G4Colour(1.0, 1.0, 0.6));

  colourWhite->SetForceSolid(true);
  colourBlue->SetForceSolid(true);
  colourLightBlue->SetForceSolid(true);
  colourGrey->SetForceSolid(true);
  colourRed->SetForceSolid(true);
  colourDark->SetForceSolid(true);
  colourVeryDark->SetForceSolid(true);
  colourGreen->SetForceSolid(true);
  colourDirtyYellow->SetForceSolid(true);
  colourDirtyWhite->SetForceSolid(true);

  l_RFA->SetVisAttributes(colourGrey);
  l_Flange1->SetVisAttributes(colourWhite);
  l_Flange2->SetVisAttributes(colourWhite);
  l_Poly10_1->SetVisAttributes(colourDirtyYellow);
  l_Poly10_2->SetVisAttributes(colourDirtyYellow);
  l_Poly10_3->SetVisAttributes(colourDirtyYellow);
  l_Poly15_1->SetVisAttributes(colourDirtyYellow);
  l_Poly15_2->SetVisAttributes(colourDirtyYellow);
  l_Poly15_3->SetVisAttributes(colourDirtyYellow);

  l_Bottom_poly->SetVisAttributes(colourDirtyYellow);

  l_Top_PV->SetVisAttributes(colourWhite);
  l_Top_plate->SetVisAttributes(colourGrey);
  l_Base_plate->SetVisAttributes(colourGrey);
  l_PMT_PV->SetVisAttributes(colourWhite);
  l_Cold_plate->SetVisAttributes(colourGrey);
  l_El_PV->SetVisAttributes(colourWhite);
  l_El_bottom->SetVisAttributes(colourGrey);
  l_FADC->SetVisAttributes(colourGreen);
  
  l_STM->SetVisAttributes(colourWhite);
  l_STM_bottom->SetVisAttributes(colourGrey);
  l_STM_top->SetVisAttributes(colourGrey);
  l_STM_baffle->SetVisAttributes(colourDirtyWhite);
  l_STM_window->SetVisAttributes(colourRed);
  l_STM_baffle_plate1->SetVisAttributes(colourDark);
  l_STM_baffle_plate2->SetVisAttributes(colourDark);
  l_STM_centre->SetVisAttributes(colourGreen);

  l_STR_baffle->SetVisAttributes(colourWhite);
  l_STR->SetVisAttributes(colourWhite);
  l_STR_bottom->SetVisAttributes(colourGrey);
  l_STR_top->SetVisAttributes(colourGrey);
  l_STR_window->SetVisAttributes(colourRed);
  l_STR_baffle_plate->SetVisAttributes(colourDark);
  l_STR_centre->SetVisAttributes(colourGreen);

  l_AMU->SetVisAttributes(colourGrey);
  l_AMU_top->SetVisAttributes(colourGrey);
  l_AMU_centre->SetVisAttributes(colourGreen);
  l_AMU_baffle->SetVisAttributes(colourWhite);

  //l_Top_PV->SetVisAttributes(G4VisAttributes::Invisible);
  //l_Top_plate->SetVisAttributes(G4VisAttributes::Invisible);
  //l_Base_plate->SetVisAttributes(G4VisAttributes::Invisible);
  //l_PMT_PV->SetVisAttributes(G4VisAttributes::Invisible);
  //l_Cold_plate->SetVisAttributes(G4VisAttributes::Invisible);
  //l_El_PV->SetVisAttributes(G4VisAttributes::Invisible);
  //l_El_bottom->SetVisAttributes(G4VisAttributes::Invisible);

  l_Mylar->SetVisAttributes(G4VisAttributes::Invisible);
  l_Tedlar->SetVisAttributes(G4VisAttributes::Invisible);
  l_PEEK->SetVisAttributes(G4VisAttributes::Invisible);
  l_RFA_mom->SetVisAttributes(G4VisAttributes::Invisible);
  //l_STM_mom->SetVisAttributes(G4VisAttributes::Invisible);
  //l_STR_mom->SetVisAttributes(G4VisAttributes::Invisible);
  //l_AMU_mom->SetVisAttributes(G4VisAttributes::Invisible);

}

StructureConstruction::~StructureConstruction(){}
