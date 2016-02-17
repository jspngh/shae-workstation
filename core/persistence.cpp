// This file will provide an interface to the database component
// The first version of this database will be purely text-based (maybe xml)

#include <iostream>
#include <sstream>
#include "serialization/XMLSerialization.h"

using namespace xmls;

class Drone: public Serializable
{
public:
	Drone();
	xString Name;
	xString MAC;
	xString longitude;
    xString latitude;
};

Drone::Drone()
{
	setClassName("Drone");
	Register("Name", &Name);
	Register("MAC", &MAC);
	Register("longitude", &longitude);
	Register("latitude", &latitude);
};

int main()
{
	// Creating the Drone object
	cout << "Creating drone object..." << endl;
	Drone *drone = new Drone();
	drone->Name="3DR Solo";
	drone->MAC="1c:87:2c:b6:39:08";
	drone->longitude="50.13";
	drone->latitude="3.64";

	// Serialize the Drone object
	cout << "Serializing object... " << endl;
	string xmlData = drone->toXML();
	cout << "OK" << endl << endl;
	cout << "Result:" << endl;
	cout << xmlData << endl << endl;

	// cout << "Login, URL:" << endl;
	// cout << "Hostname: " << settings->Login.HostName.value();
	// cout << ":" << settings->Login.Port.toString() << endl << endl;
	// cout << "Show all collection items" << endl;
	// for (size_t i=0; i<settings->LastUsedDocuments.size(); i++)
	// {
	// 	LastUsedDocument* doc = settings->LastUsedDocuments.getItem(i);
	// 	cout << "Item " << i << ": " << doc->Name.value() << endl;
	// }
	// cout << endl;
    //
	// cout << "Deserialization:" << endl;
	// cout << "Class version: " << Serializable::IdentifyClassVersion(xmlData) << endl;
	// cout << "Performing deserialization..." << endl;
    //
	// // Deserialize the XML text
	// ApplicationSettings* dser_Settings=new ApplicationSettings;
	// if (Serializable::fromXML(xmlData, dser_Settings))
	// {
	// 	cout << "OK" << endl << endl;
    //
	// 	// compare both objects
	// 	cout << "Compareing objects: ";
	// 	if (dser_Settings->Compare(settings))
	// 		cout << "equal" << endl << endl; else
	// 		cout << "net equal" << endl << endl;
    //
	// 	// now set value
	// 	cout << "Set new value for field >password<..." << endl;
	// 	dser_Settings->Login.Password = "newPassword";
	// 	cout << "OK" << endl << endl;
    //
	// 	cout << "compare objects again: ";
	// 	if (dser_Settings->Compare(settings))
	// 		cout << "equal" << endl << endl; else
	// 		cout << "net equal" << endl << endl;
    //
    //
	// 	cout << "search and replace placeholders: ";
	// 	dser_Settings->Replace("{FILEPATH}", "c:\\temp\\");
	// 	cout << "OK" << endl << endl;
    //
	// 	//output xml-data
	// 	cout << "Serialize and output xml data: " << endl;
	// 	cout << dser_Settings->toXML() << endl << endl;
    //
	// 	cout << "Clone object:" << endl;
	// 	ApplicationSettings *clone1(new ApplicationSettings);
	// 	Serializable::Clone(dser_Settings, clone1);
	// 	cout << "Serialize and output clone: " << endl;
	// 	cout << clone1->toXML() << endl << endl;
	// 	delete (clone1);
	// }

	delete(drone);
	// delete(dser_Settings);
	getchar();
	return 0;
}
