#include "argumentsHandler.h"
argument::argument(int id, char *shortName, char *longName, char *description, char *expected)
{
	this->id = id;
	this->longName = longName;
	this->shortName = shortName;
	this->description = description;
	this->expected = expected;
}

void argumentsHandler::add(argument arg)
{
	arguments.push_back(arg);
}

argumentsHandler::argumentsHandler(int argc, char *argv[])
{
	this->separator = (char *)":";
	this->shortPrefix = (char *)"-";
	this->longPrefix = (char *)"--";
	this->argc = argc;
	char **curarg;
	int i;

	for (curarg = argv, i = 0; //initialize curarg to argv array and i to 0
		 *curarg != NULL;	  //stop when curarg references NULL
		 curarg++, i++)
	{ //increment curarg and i
		this->argv[i] = *curarg;
	}

	this->index = 1;
}

argumentsHandler::~argumentsHandler()
{
}

int argumentsHandler::getAction()
{
	//If there isn't argument:
	if (argc == 1)
	{
		showHelp();
		return -1;
	}

	//If index > arguments
	if (index == argc)
	{
		return -1;
	}

	value = "";
	std::string parm = argv[index];
	index++;
	size_t point = parm.find(this->separator);
	std::string key;

	//If does no find ":" continue
	if (point == std::string::npos)
	{
		key = parm;
		value = "";
	}
	else
	{
		//get key:
		key = parm.substr(0, point);
		//get value:
		value = parm.substr(point + 1);
	}

	for (int i = 0; i < arguments.size(); i++)
	{
		argument arg = arguments[i];

		if (key.compare(concatchar(longPrefix, arg.longName)) == 0 ||
			key.compare(concatchar(shortPrefix, arg.shortName)) == 0)
		{
			return i;
		}
	}

	return -1;
}
void argumentsHandler::pvalue(char *destination, int length)
{
	 const char *t = value.c_str();
	//strcpy_s(destination, length - 1, t);
	memcpy(destination, t, length);
}

void argumentsHandler::pvalue(int *destination)
{
	int t = stoi(value.c_str());
	memcpy(destination, &t, sizeof(int));
}

void argumentsHandler::pvalue(long *destination)
{
	long t = stol(value.c_str());
	memcpy(destination, &t, sizeof(long));
}

void argumentsHandler::pvalue(double *destination)
{
	double t = stod(value.c_str());
	memcpy(destination, &t, sizeof(double));
}

void argumentsHandler::pvalue(int64 *destination)
{

	try {
		int64  t = stoull(value.c_str());
		memcpy(destination, &t, sizeof(int64));
	}
	catch (out_of_range ex) {
		cout << "Exception: Number is bigger than int64 {system: " << ex.what() << "}" << endl;
	}

}

void argumentsHandler::showHelp()
{
	printf("%s", "Arguments:\n");
	printf("%s", "---------------------------\n");
	// printf("%s\t\t%s\t%s", "Short form", "Long form", "Description\n");

	for (int i = 0; i < arguments.size(); i++)
	{
		argument arg = arguments[i];
		if (strlen(arg.expected) > 0)
		{
			printf("%-20s", concatchar(shortPrefix, arg.shortName, separator, arg.expected));
			printf("%-20s", concatchar(longPrefix, arg.longName, separator, arg.expected));
			printf("%s\n", arg.description);
		}
		else
		{
			printf("%-20s", concatchar(shortPrefix, arg.shortName));
			printf("%-20s", concatchar(longPrefix, arg.longName));
			printf("%s\n", arg.description);
		}
	}
}
