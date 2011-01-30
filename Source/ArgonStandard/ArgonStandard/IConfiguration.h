#ifndef _ICONFIGURATION_HEADER_
#define _ICONFIGURATION_HEADER_

#include <Standard/ArgonAny.h>
#include <Standard/ArgonQString.h>

namespace Argon
{
	DeclareBasedInterface(IConfiguration, IArgonUnknown)

		enum EngineConfigurationType
		{
			CONFIGURATIONTYPE_Custom = 0,
			CONFIGURATIONTYPE_Preformance,
			CONFIGURATIONTYPE_Quality,
		};

		///LOADCONFIG(VOID)
		///
		///Load the current configuration
		///
		///No Params:
		void LoadConfig() = 0;

		///SAVECONFIG(VOID)
		///
		///Save the current configuration settings
		///
		///No Params:
		void SaveConfig() = 0;

		///SETFILENAME(VOID)
		///
		/// Set the filename that the configuration file will save to and load from
		///
		///Param FileName: Set the Configuration FileName
		void SetFileName(String FileName) = 0;

		///GETSYSTEMCONFIGURATION(VOID)
		///
		///Get the users system configuration and add information
		///
		///No Params:
		void GetSystemConfiguration(EngineConfigurationType ConfigurationType) = 0;

		///ADDITEM(VOID)
		///
		///Add a Item to the Configuration to get the Item simply use the name in the function GEITEMVALUE
		///
		///Param Name: The name of the Item that will be added
		///Param Value: The Value that will be assigned to the Name
		void AddItem(QString Name, Any Value);

		Any GetItemValue(QString Name);

	EndInterface( IConfiguration )
	
} //Namespace

#endif //_ICONFIGURATION_HEADER_