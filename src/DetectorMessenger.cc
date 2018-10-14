//
//  DetectorMessenger.cc 2013-12-18  Maxime Chauvin
//

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* det): detector(det)
{
  RotationCmd = new G4UIcmdWithADoubleAndUnit("/PoGOLite/SetPolarimeterRot",this);
  RotationCmd->SetGuidance("Set rotation of the polarimeter");
  RotationCmd->SetParameterName("Rotation",false);
  RotationCmd->SetUnitCategory("Angle");
  RotationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ElevationCmd = new G4UIcmdWithADoubleAndUnit("/PoGOLite/SetElevation",this);
  ElevationCmd->SetGuidance("Set elevation of the polarimeter");
  ElevationCmd->SetParameterName("Rotation",false);
  ElevationCmd->SetUnitCategory("Angle");
  ElevationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
  delete RotationCmd;
  delete ElevationCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == RotationCmd )
   { detector->SetPolarimeterRot(RotationCmd->GetNewDoubleValue(newValue));}
  if( command == ElevationCmd )
   { detector->SetElevation(ElevationCmd->GetNewDoubleValue(newValue));}
}
