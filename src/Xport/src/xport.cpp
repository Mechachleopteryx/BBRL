
#include "xport.h"

using namespace std;
using namespace utils;


// ===========================================================================
//	Functions
// ===========================================================================
vector<xport::AgentData> xport::getAgentDataList(int argc, char* argv[])
{
     vector<xport::AgentData> agentDataList;
     vector<string> notLoaded;


     //   1.   Parse the Agents
          //   Case 1:   '--agent --agent_file'
     int iAgent = 0;
     while (true)
     {
          while ((string(argv[iAgent]) != "--agent") && (iAgent < (argc - 1)))
               ++iAgent;
   
          if ((iAgent + 3) >= (argc - 1)) { break; }
   
          int argcBis = 5;
          char** argvBis = new char*[argcBis];
          argvBis[0] = argv[0];
          argvBis[1] = argv[iAgent++];
          argvBis[2] = argv[iAgent++];
          argvBis[3] = argv[iAgent++];
          argvBis[4] = argv[iAgent++];


          Agent* agent = 0;
          try { agent = Agent::parse(argcBis, argvBis); }
          catch (parsing::ParsingException&) {}
          delete[] argvBis;

          
          xport::AgentData agentData;
          if (agent)
          {
               agentData.loadAgent(agent);
               delete agent;
          }
          else { notLoaded.push_back(string(argvBis[4])); }
          agentDataList.push_back(agentData);
     }
     
          //   Case 2:   '--agent_files'
     try
     {
          string file = parsing::getValue(argc, argv, "--agent_files");
          ifstream is(file.c_str());
          
          string agentName, agentFileName;
          while (getline(is, agentName))
          {
               if (getline(is, agentFileName))
               {
                    int argcBis = 5;
                    char** argvBis = new char*[argcBis];
                    argvBis[0] = argv[0];
                    
                    string tmp = "--agent";
                    argvBis[1] = new char[tmp.size() + 1];
                    tmp.copy(argvBis[1], tmp.size());
                    argvBis[1][tmp.size()] = '\0';                    
                    
                    tmp = agentName.c_str();
                    argvBis[2] = new char[tmp.size() + 1];
                    tmp.copy(argvBis[2], tmp.size());
                    argvBis[2][tmp.size()] = '\0';
                    
                    tmp = "--agent_file";
                    argvBis[3] = new char[tmp.size() + 1];
                    tmp.copy(argvBis[3], tmp.size());
                    argvBis[3][tmp.size()] = '\0';
                    
                    tmp = agentFileName.c_str();
                    argvBis[4] = new char[tmp.size() + 1];
                    tmp.copy(argvBis[4], tmp.size());
                    argvBis[4][tmp.size()] = '\0';
                    
                    
                    Agent* agent = 0;
                    try { agent = Agent::parse(argcBis, argvBis); }
                    catch (parsing::ParsingException&) {}
                    delete[] argvBis;

          
                    xport::AgentData agentData;
                    if (agent)
                    {
                         agentData.loadAgent(agent);
                         delete agent;
                    }
                    else { notLoaded.push_back(string(argvBis[4])); }
                    agentDataList.push_back(agentData);
               }
          }
     }
     catch (parsing::ParsingException&) {}
     
     
     
     //   2.   Parse the Experiments
          //   Case 1:   '--experiment --experiment_file'
     int iExp = 0, nExp = 0;
     while (iExp < (argc - 1))
     {
          while ((string(argv[iExp]) != "--experiment") && (iExp < (argc - 1)))
               ++iExp;
          
          if ((iExp + 1) >= (argc - 1)) { break; }
          
          int argcBis = 4;
          char** argvBis = new char*[argcBis];
          argvBis[0] = argv[0];
          argvBis[1] = argv[iExp++];
          argvBis[2] = argv[iExp++];
          argvBis[3] = argv[iExp++];


          Experiment* exp = 0;
          try { exp = Experiment::parse(argcBis, argvBis); }
          catch (parsing::ParsingException&) {}
          delete[] argvBis;

          
          if (exp)
          {
               agentDataList[nExp].loadExperiment(exp);
               delete exp;
          }
          else { notLoaded.push_back(string(argvBis[3])); }
          ++nExp;
     }
     
          //   Case 2:   '--experiment_files'
     try
     {
          string file = parsing::getValue(argc, argv, "--experiment_files");
          ifstream is(file.c_str());
          
          string expFileName;
          while (getline(is, expFileName))
          {
               int argcBis = 4;
               char** argvBis = new char*[argcBis];
               argvBis[0] = argv[0];
               
               string tmp = "--experiment";
               argvBis[1] = new char[tmp.size() + 1];
               tmp.copy(argvBis[1], tmp.size());
               argvBis[1][tmp.size()] = '\0';
               
               tmp = "--experiment_file";
               argvBis[2] = new char[tmp.size() + 1];
               tmp.copy(argvBis[2], tmp.size());
               argvBis[2][tmp.size()] = '\0';
               
               tmp = expFileName.c_str();
               argvBis[3] = new char[tmp.size() + 1];
               tmp.copy(argvBis[3], tmp.size());
               argvBis[3][tmp.size()] = '\0';
               
               
               Experiment* exp = 0;
               try { exp = Experiment::parse(argcBis, argvBis); }
               catch (parsing::ParsingException&) {}
               delete[] argvBis;

     
               if (exp)
               {
                    agentDataList[nExp].loadExperiment(exp);
                    delete exp;
               }
               else { notLoaded.push_back(string(argvBis[3])); }
               ++nExp;
          }
     }
     catch (parsing::ParsingException&) {}
     
     
     //   3.   Remove the AgentData's which have not been loaded correctly
     vector<AgentData> fAgentDataList;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
     {
          if (agentDataList[i].isAgentLoaded()
                    && agentDataList[i].isExperimentLoaded())
               fAgentDataList.push_back(agentDataList[i]);
     }
     

     //   4.   Print the list of files which have not been loaded correctly
     if (!notLoaded.empty())
     {
          cout << "\n\t";
          cout << "WARNING: Some data are missing (" << notLoaded.size() << ")\n";

          for (unsigned int i = 0; i < notLoaded.size(); ++i)
               cout << "\t\t" << notLoaded[i] << "\n";
          cout << "\n";
     }
     
     
     //   4.   Return
     return fAgentDataList;
}


// ---------------------------------------------------------------------------
//   getList()
// ---------------------------------------------------------------------------
vector<string> xport::getList(const vector<xport::AgentData>& agentDataList,
                              xport::StrField field)
{
     vector<unsigned int> list;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
          list.push_back(i);
     
     return getList(list, agentDataList, field);
}


vector<string> xport::getList(const vector<unsigned int>& list,
                              const vector<xport::AgentData>& agentDataList,
                              xport::StrField field)
{
     vector<string> fList;
     for (unsigned int i = 0; i < list.size(); ++i)
     {
          const xport::AgentData& data = agentDataList[list[i]];
          string fieldV = data.getField(field);
          
          bool found = false;
          for (unsigned int j = 0; j < fList.size(); ++j)
               if (fieldV == fList[j]) { found = true; break; }
          
          if (!found) { fList.push_back(fieldV); }
     }
     return fList;
}


// ---------------------------------------------------------------------------
//   filter()
// ---------------------------------------------------------------------------
vector<unsigned int> xport::filter(
          const vector<xport::AgentData>& agentDataList,
          xport::StrField field,
          xport::StrFilterCondition condition,
	     string cStr)
{
     vector<unsigned int> list;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
          list.push_back(i);
     
     return filter(list, agentDataList, field, condition, cStr);
}


vector<unsigned int> xport::filter(
          const vector<unsigned int>& list,
          const vector<xport::AgentData>& agentDataList,
          xport::StrField field,
          xport::StrFilterCondition condition,
	     string cStr)
{
     vector<unsigned int> filteredList;
     for (unsigned int i = 0; i < list.size(); ++i)
     {
          const xport::AgentData& data = agentDataList[list[i]];
          string fieldV = data.getField(field);
          switch (condition)
          {
               case STR_EQUAL:
                    if (fieldV == cStr) { filteredList.push_back(list[i]); }
                    break;

               case STR_NOT_EQUAL:
                    if (fieldV != cStr) { filteredList.push_back(list[i]); }
                    break;

               case STR_SUBSTR:
                    if (fieldV.find(cStr) != std::string::npos)
                         filteredList.push_back(list[i]);
                    break;

               case STR_NOT_SUBSTR:
                    if (fieldV.find(cStr) == std::string::npos)
                         filteredList.push_back(list[i]);
                    break;
          }
     }
     return filteredList;
}


vector<unsigned int> xport::filter(
          const vector<xport::AgentData>& agentDataList,
          xport::DblField field,
	     xport::DblFilterCondition condition,
	     double value)
{
     vector<unsigned int> list;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
          list.push_back(i);
     
     return filter(list, agentDataList, field, condition, value);
}


vector<unsigned int> xport::filter(
          const vector<unsigned int>& list,
          const vector<xport::AgentData>& agentDataList,
          xport::DblField field,
	     xport::DblFilterCondition condition,
	     double value)
{
     vector<unsigned int> filteredList;
     for (unsigned int i = 0; i < list.size(); ++i)
     {
          const xport::AgentData& data = agentDataList[list[i]];
          double fieldV = data.getField(field);
          switch (condition)
          {
               case DBL_BELOW:
                    if (fieldV < value)  { filteredList.push_back(list[i]); }
                    break;

               case DBL_BELOW_EQUAL:
                    if (fieldV <= value) { filteredList.push_back(list[i]); }
                    break;

               case DBL_EQUAL:
                    if (fieldV == value) { filteredList.push_back(list[i]); }
                    break;

               case DBL_ABOVE_EQUAL:
                    if (fieldV >= value) { filteredList.push_back(list[i]); }
                    break;

               case DBL_ABOVE:
                    if (fieldV > value)  { filteredList.push_back(list[i]); }
                    break;
          }
     }
     return filteredList;
}


// ---------------------------------------------------------------------------
//   getMin()
// ---------------------------------------------------------------------------
int xport::getMin(const vector<xport::AgentData>& agentDataList,
                  xport::DblField field)
{
     vector<unsigned int> list;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
          list.push_back(i);
     
     return getMin(list, agentDataList, field);
}


int xport::getMin(const vector<unsigned int>& list,
                  const vector<xport::AgentData>& agentDataList,
                  xport::DblField field)
{
     int min = -1;
     double minV;
     for (unsigned int i = 0; i < list.size(); i++)
     {
          const xport::AgentData& data = agentDataList[list[i]];
          double fieldV = data.getField(field);
          
          if ((min == -1) || (fieldV < minV))
          {
               min = list[i];
               minV = fieldV;
          }
     }
     return min;
}


int xport::getMin(const vector<const xport::AgentData*>& agentDataList,
                  xport::DblField field)
{
     int min = -1;
     double minV;
     for (unsigned int i = 0; i < agentDataList.size(); i++)
     {
          const xport::AgentData* data = agentDataList[i];
          double fieldV = data->getField(field);
          
          if ((min == -1) || (fieldV < minV))
          {
               min = i;
               minV = fieldV;
          }
     }
     return min;
}


// ---------------------------------------------------------------------------
//   getMax()
// ---------------------------------------------------------------------------
int xport::getMax(const vector<xport::AgentData>& agentDataList,
                  xport::DblField field)
{
     vector<unsigned int> list;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
          list.push_back(i);
     
     return getMax(list, agentDataList, field);
}


int xport::getMax(const vector<unsigned int>& list,
                  const vector<AgentData>& agentDataList,
                  xport::DblField field)
{
     int max = -1;
     double maxV;
     for (unsigned int i = 0; i < list.size(); i++)
     {
          const xport::AgentData& data = agentDataList[list[i]];
          double fieldV = data.getField(field);
          
          if ((max == -1) || (fieldV > maxV))
          {
               max = list[i];
               maxV = fieldV;
          }
     }
     return max;
}


int xport::getMax(const vector<const AgentData*>& agentDataList,
                  xport::DblField field)
{
     int max = -1;
     double maxV;
     for (unsigned int i = 0; i < agentDataList.size(); i++)
     {
          const xport::AgentData* data = agentDataList[i];
          double fieldV = data->getField(field);
          
          if ((max == -1) || (fieldV > maxV))
          {
               max = i;
               maxV = fieldV;
          }
     }
     return max;
}


// ---------------------------------------------------------------------------
//   sort()
// ---------------------------------------------------------------------------
vector<unsigned int> xport::sort(
          const vector<xport::AgentData>& agentDataList,
          xport::DblField field, bool ascendingOrder)
{
     vector<unsigned int> list;
     for (unsigned int i = 0; i < agentDataList.size(); ++i)
          list.push_back(i);
     
     return sort(list, agentDataList, field, ascendingOrder);
}
     
     
vector<unsigned int> xport::sort(
          const vector<unsigned int>& list,
          const vector<xport::AgentData>& agentDataList,
          xport::DblField field, bool ascendingOrder)
{
     //   Save the original indexes
     map<unsigned int, unsigned int> m;
     for (unsigned int i = 0; i < list.size(); ++i) { m[i] = list[i]; }     
     
     
     //   Copy the list
     vector<const AgentData*> cAgentDataList;
     for (unsigned int i = 0; i < list.size(); ++i)
          cAgentDataList.push_back(&agentDataList[list[i]]);


     //   Sort the list
     vector<unsigned int> sortedList;
     while (!cAgentDataList.empty())
     {
          //   Find the largest/smallest
          unsigned int s;
          if (ascendingOrder) { s = xport::getMin(cAgentDataList, field); }
          else                { s = xport::getMax(cAgentDataList, field); }
          
          
          //   Add its index to 'sortedList'
          sortedList.push_back(m[s]);
          
          
          //   Updated the map
          m[s] = m[cAgentDataList.size() - 1];
          
          
          //   Remove the element found from the current list
          cAgentDataList[s] = cAgentDataList.back();
          cAgentDataList.pop_back();
     }
     return sortedList;
}
