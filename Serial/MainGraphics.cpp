#pragma once
#include "Engine.h"
#include "common.h"

using namespace std;

SerialCommunication serial;
void InitSerial()
{
	int * port = &serial.commport;
	cout << "Enter comm port: ";
	cin >> *port;
	cout << endl;
	cout << "Estblishing communication in COM Port: " << *port << endl;
}
int main(int argc, char **argv)
{
	InitSerial();
	Engine* engine = new Engine();
	
	if(engine->Init())
		engine->Run();

	delete engine;
	return 0;
}
