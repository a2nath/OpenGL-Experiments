#pragma once
#include <windows.h>


namespace Controller
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Data;
	using namespace System::IO::Ports;

	class SerialCommunication
	{
	public:
		int commport;
	};
}