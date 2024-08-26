#include <iostream>
#include <cmath>
#include <map>
#include <string>

// Rocket equation, 
double rocketEquationDeltaV(std::map<std::string, double> engineSpecs, std::map<std::string, double> rocketSpecs)
{
	
	double emptyMass = rocketSpecs["Empty Mass"];
	double propellantMass = rocketSpecs["Propellant Mass"];
	double payloadMass = rocketSpecs["Payload Mass"];

	double ISP = engineSpecs["ISP"];
	double massRatio = (emptyMass + payloadMass + propellantMass) / (emptyMass + payloadMass);
	
	double deltaV = (ISP * 9.81) * log(massRatio);
	return deltaV;
}

void rocketEquationPayload(std::map<std::string, double> engineSpecs, std::map<std::string, double> rocketSpecs, std::map<std::string, double> orbit, std::string orbitChoice)
{

	double emptyMass = rocketSpecs["Empty Mass"];
	double propellantMass = rocketSpecs["Propellant Mass"];
	double deltaV = orbit[orbitChoice];
	double ISP = engineSpecs["ISP"];

	double payloadMassForGivenDeltaV = (propellantMass + emptyMass * (1 - exp(deltaV/(9.81*ISP)))) / ((exp(deltaV/(9.81*ISP))) - 1);
	std::cout << std::endl << "Maximum payload to " << orbitChoice << " is " << payloadMassForGivenDeltaV << " kg " << std::endl;
	
}

void displayEngineSpecs(std::map<std::string, double> name)
{
		std::cout << "Thrust (kN): " << name["Thrust"] << std::endl
		<< "Specific Impulse (sec): " << name["ISP"] << std::endl
		<< "Mixture Ratio (Oxidizer to Fuel Flow): " << name["Mixture Ratio"] << std::endl
		<< "Chamber Pressure (bar): " << name["Chamber Pressure"] << std::endl
		<< "Nozzle Exit Area Ratio: " << name["Nozzle Exit Area Ratio"] << ":1" << std::endl
		<< "Inert Engine Mass (kg): " << name["Inert Engine Mass"] << std::endl;
}

void payloadDecisionStructure(std::map<std::string, double> engineSpecs, std::map<std::string, double> rocketSpecs, std::map<std::string, double> orbit, double payloadInput)
{
	rocketSpecs["Payload Mass"] = payloadInput;
	double deltaV = rocketEquationDeltaV(engineSpecs, rocketSpecs);
	if (deltaV >= orbit["Lunar Orbit"])
	{
		std::cout << "Your payload is able to reach lunar, geosynchronous and low earth orbit" << std::endl;
	}
	else if (deltaV >= orbit["GEO"])
	{
		std::cout << "Your payload is able to geosynchronous and low earth orbit" << std::endl;
	}
	else if (deltaV >= orbit["LEO"])
	{
		std::cout << "Your payload is able to reach low earth orbit" << std::endl;
	}
	else
	{
		std::cout << "Your payload is unable to reach earth's orbit" << std::endl;
	}
}

void destinationDecisionStructure(std::map<std::string, double> engineSpecs, std::map<std::string, double> rocketSpecs, std::map<std::string, double> orbit)
{
	int num = 0;
	while (num != -1)
	{
		std::cout << std::endl << "Choose your destination [-1 to Exit]" << std::endl;
		std::cout << "1. " << "Low Earth Orbit (LEO)" << std::endl;
		std::cout << "2. " << "Geosynchronous Orbit (GEO)" << std::endl;
		std::cout << "3. " << "Lunar Orbit" << std::endl;

		std::cin >> num;
		std::string LEO = "LEO";
		std::string GEO = "GEO";
		std::string LNO = "Lunar Orbit";

		switch (num)
		{
		case 1:
			rocketEquationPayload(engineSpecs, rocketSpecs, orbit, LEO);
			break;
			

		case 2:
			rocketEquationPayload(engineSpecs, rocketSpecs, orbit, GEO);
			break;

		case 3:
			rocketEquationPayload(engineSpecs, rocketSpecs, orbit, LNO);
			break;

		default:
			std::cout << "Invalid choice. Please Try again";
			break;
		}
		
	}
}

void mainDecisionStructure(std::map<std::string, double> engineSpecs, std::map<std::string, double> rocketSpecs, std::map<std::string, double> orbit, std::string spacecraftName, std::string spacecraftInfo)
{
	int num = 0;
	while (num != -1)
	{
		std::cout << std::endl << "Choose an option [-1 to Exit]" << std::endl;
		std::cout << "1. " << "Choose the destination of your payload" << std::endl;
		std::cout << "2. " << "How far can your payload go" << std::endl;
		std::cout << "3. " << "Display engine specifications" << std::endl;
		std::cin >> num;
		double payloadInput;
		switch (num)
		{
		case 1:
			
			destinationDecisionStructure(engineSpecs, rocketSpecs, orbit);

			break;

		case 2:

			std::cout << std::endl << "Enter the mass of your payload" << std::endl;
			std::cin >> payloadInput;
			payloadDecisionStructure(engineSpecs, rocketSpecs, orbit, payloadInput);
			break;

		case 3:

			std::cout << std::endl << spacecraftName << std::endl << "Propulsion System Designation : " << spacecraftInfo << std::endl;
			displayEngineSpecs(engineSpecs);
			break;

		default:
			std::cout << "Invalid choice. Please Try again";
			break;
		}
		
	}
}

// Main Function
int main()
{
	std::map<std::string, double> atlasV
	{
		std::pair<std::string, double>("Empty Mass", 2316),
		std::pair<std::string, double>("Propellant Mass", 20830),
		std::pair<std::string, double>("Payload Mass", 18850)
	};

	std::map<std::string, double> RL10Vac
	{
		std::pair<std::string, double>("Thrust", 110.1),
		std::pair<std::string, double>("ISP", 465.5),
		std::pair<std::string, double>("Mixture Ratio", 5.88),
		std::pair<std::string, double>("Chamber Pressure", 107),
		std::pair<std::string, double>("Nozzle Exit Area Ratio", 84),
		std::pair<std::string, double>("Inert Engine Mass", 301)
	};

	std::map<std::string, double> deltaIV
	{
		std::pair<std::string, double>("Empty Mass", 3490),
		std::pair<std::string, double>("Propellant Mass", 27220),
		std::pair<std::string, double>("Payload Mass", 28790)
	};

	std::map<std::string, double> Falcon9
	{
		std::pair<std::string, double>("Empty Mass", 3900),
		std::pair<std::string, double>("Propellant Mass", 92670),
		std::pair<std::string, double>("Payload Mass", 22800)
	};

	std::map<std::string, double> MerlinVac
	{
		std::pair<std::string, double>("Thrust", 981),
		std::pair<std::string, double>("ISP", 348),
		std::pair<std::string, double>("Mixture Ratio", 2.72),
		std::pair<std::string, double>("Chamber Pressure", 42),
		std::pair<std::string, double>("Nozzle Exit Area Ratio", 36.4),
		std::pair<std::string, double>("Inert Engine Mass", 490),
		std::pair<std::string, double>("Empty Mass", 3900),
		std::pair<std::string, double>("Propellant Mass", 92670),
		std::pair<std::string, double>("Payload Mass", 22800)
	};

	std::map<std::string, double> atlasOrbits
	{
		std::pair<std::string, double>("LEO", 3169.02),
		std::pair<std::string, double>("GEO", 6969.02),
		std::pair<std::string, double>("Lunar Orbit", 7269.02)
	};

	std::map<std::string, double> deltaOrbits
	{
		std::pair<std::string, double>("LEO", 2224.179),
		std::pair<std::string, double>("GEO", 6024.18),
		std::pair<std::string, double>("Lunar Orbit", 6324.179)
	};

	std::map<std::string, double> falconOrbits
	{
		std::pair<std::string, double>("LEO", 5269),
		std::pair<std::string, double>("GEO", 9069),
		std::pair<std::string, double>("Lunar Orbit", 9369)
	};


	
	int num = 0;
	std::string spacecraft1 = "Atlas V";
	std::string spacecraft2 = "Delta IV Heavy";
	std::string spacecraft3 = "Falcon 9";
	std::string info1 = "RL-10 Vac (Liquid Oxygen/Liquid Hydrogen)";
	std::string info2 = "RL-10 Vac (Liquid Oxygen/Liquid Hydrogen)";
	std::string info3 = "Merlin (Liquid Oxygen/Kerosene)";
		

	while (num != -1)
	{
		std::cout << "Choose your spacecraft [-1 to Exit]" << std::endl;
		std::cout << "1. Atlas V" << std::endl;
		std::cout << "2. Delta IV Heavy" << std::endl;
		std::cout << "3. Falcon 9" << std::endl;
		std::cin >> num;

		switch (num)
		{
		case 1:
			mainDecisionStructure(RL10Vac, atlasV, atlasOrbits, spacecraft1, info1);
			break;

		case 2:
			mainDecisionStructure(RL10Vac, deltaIV, deltaOrbits, spacecraft2, info2);
			break;

		case 3:
			mainDecisionStructure(MerlinVac, Falcon9, falconOrbits, spacecraft3, info3);
			break;

		default:
			std::cout << "Invalid choice. Please Try again";
			break;
		}
		num = -1;
	}


	




}