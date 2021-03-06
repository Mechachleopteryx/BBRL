
#ifndef DDS_H
#define DDS_H

#include "../ExternalLibs.h"


// ===========================================================================
/**
	\namespace	dds
	\author 		Castronovo Michael
	
	\brief		A namespace gathering the tools and classes related to
	               RL problems with Discrete state space, Discrete action
	               space and Single reward.
					
				This namespace gathers the Agents, MDPs, MDPDistributions
				and Experiments in this particular setting.
				
	\date		2015-12-18
*/
// ===========================================================================
namespace dds
{
	// ======================================================================
	//	Constants
	// ======================================================================
	/**
		\brief	The accuracy level to use by the algorithms
				(e.g.: value-iteration / q-iteration)
	*/
	const double ACCURACY = 1e-2;
	
	
	/**
		\brief	The accuracy level of the representation of '0'.
				(e.g.: the sum of the probability values in the transition
				matrix of an MDP is not exactly '1.0' in every case)
	*/
	const double ZERO_ACCURACY = 1e-9;
	
	
	// ======================================================================
	//	Functions
	// ======================================================================
	/**
          \brief         Perfom some initialization tasks for the 'DDS' package
				     and initializes the RNG's.
          
          \param[seed    The seed to use to initialize the RNG.
                         (0: random seed, using 'time(0)')
	*/	
	void init(unsigned int seed = 0);

	
	// ======================================================================
	//	Classes
	// ======================================================================
	/**
          \class    Agent
          \brief    Interface of an RL agent to address MDPs.
	*/
	class Agent;
	
	
	/**
          \class    RandomAgent
          \brief    A RL agent taking random decisions.
	*/
	class RandomAgent;
	
	
	/**
          \class    OptimalAgent
          \brief 	A RL agent taking optimal decisions.
	*/
	class OptimalAgent;
	
	/**
          \class    EOptimalAgent
          \brief 	A RL agent which adds a probability of 'epsilon' to take
	               a random decision to an Agent.
	*/
	class EAgent;


	/**
	     \class    EGreedyAgent
	     \brief 	A RL Agent following an e-greedy policy.
	*/
	class EGreedyAgent;


     /**
          \class    SoftMaxAgent
          \brief 	A RL Agent following a soft-max policy.
     */
	class SoftMaxAgent;
	
	
	/**
          \class    VDBEEGreedyAgent
          \brief 	A RL Agent following an vdbe e-greedy policy.
	*/
	class VDBEEGreedyAgent;
	
	
	/**
	     \class    FormulaAgent
          \brief 	A RL Agent following a policy parametrized by a formula.
	*/
	class FormulaAgent;
	
	
	/**
          \class    FormulaVector
          \brief 	Defines a std::vector of formulas which also add
                    serialization.
	*/
	class FormulaVector;
	
	
	/**
          \class    BAMCPAgent
          \brief 	A RL Agent following a BAMCP policy.
	*/
	class BAMCPAgent;
	
	
	/**
          \class    BFS3Agent
          \brief 	A RL Agent following a BFS3 policy.
	*/
	class BFS3Agent;
	
	
	/**
          \class    SBOSSAgent
          \brief 	A RL Agent following a SBOSS policy.
	*/
	class SBOSSAgent;
	
	
	/**
          \class    BEBAgent
          \brief 	A RL Agent following a BEB policy.
	*/
	class BEBAgent;
	
	
	/**
	     \class    OPPSDSAgent
	     \brief 	A RL agent which applies the OPPS meta-learning algorithm
	               during its offline phase (discrete case).
	*/
	class OPPSDSAgent;
	
	
	/**
	     \class    OPPSCSAgent
	     \brief 	A RL agent which applies the OPPS meta-learning algorithm
	               during its offline phase (continuous case).
	*/
	class OPPSCSAgent;
	
	
	/**
	     \class    SLAgent
	     \brief    A RL agent copying another agent using a supervised learning
	               algorithm.
	*/
	class SLAgent;
	
	
	/**
          \class    ANNAgent
          \brief    A RL agent based on a DNN trained during the offline phase.
	*/
	class ANNAgent;


     /**
          \class    FVariable
          \brief 	Represent a variable for the FormulaAgent's.
     */
     class FVariable;
     
     
     /**
          \class    FVariableVector
          \brief 	Defines a std::vector of FVariables which also add
                    serialization.
     */
     class FVariableVector;
     
     
     /**
          \class    FVariableException
          \brief    Exception.
     */
     class FVariableException;
     
     
     /**
          \class    QVar
          \brief 	A variable for the FormulaAgent's, which represents a
	               Q-function model-based variable for FormulaAgent.
     */
     class QVar;
     
     
     /**
          \class    QMean
          \brief 	A variable for the FormulaAgent's, which represents a
	               Q-function based on the mean model of a prior distribution.
     */
	class QMean;
	
	
	/**
          \class    QSelf
          \brief 	A variable for the FormulaAgent's, which represents a
	               Q-function based on the 'self' model of a prior
	               distribution.
     */
	class QSelf;
	
	
	/**
          \class    QUniform
          \brief 	A variable for the FormulaAgent's, which represents a
	               Q-function based on the 'uniform' model of a prior
	               distribution.
     */
	class QUniform;
	
	
	/**
          \class    QCounterVar
          \brief    A variable for the FormulaAgent's, which represents a
	               Q-function based on counter model.
     */
	class QCounterVar;
	
	
	/**
          \class    AgentFactory
          \brief    Interface of an AgentFactory to generate RL Agents.
	*/
	class AgentFactory;
	
	
	/**
          \class    AgentFactoryException
          \brief    Exception.
	*/
	class AgentFactoryException;
	
	
	/**
          \class    EGreedyAgentFactory
          \brief 	An AgentFactory which generates EGreedyAgent's.
	*/
	class EGreedyAgentFactory;
	
	
	/**
          \class    SoftMaxAgentFactory
          \brief 	An AgentFactory which generates SoftMaxAgent's.
	*/
	class SoftMaxAgentFactory;
	
	
	/**
          \class    VDBEEGreedyAgentFactory
          \brief 	An AgentFactory which generates VDBEEGreedyAgent's.
	*/
	class VDBEEGreedyAgentFactory;
	
	
	/**
          \class    FormulaAgentFactory
          \brief 	An AgentFactory which generates FormulaAgent's
                    (where the formulas are polynomials).
	*/
	class FormulaAgentFactory;
	
	
	/**
	     \class    SLAgentFactory
	     \brief    An AgentFactory which generates SLAgent's.
	               (i)  The SLAgentFactory use another AgentFactory for
                         generating the Agent corresponding to the given
                         parameters.
                    (ii) The generated Agent is copied by a SLAgent, and
                         the SLAgent is returned.
	*/
	class SLAgentFactory;
		
	
	/**
	     \class    ANNAgentFactory
	     \brief    An AgentFactory which generates ANNAgent's.
	               (i)  The ANNAgentFactory use another AgentFactory for
                         generating the Agent corresponding to the given
                         parameters.
                    (ii) The generated Agent is copied by a ANNAgent, and
                         the ANNAgent is returned.
	*/
	class ANNAgentFactory;
	
	
	/**
          \class    MDP
          \brief 	Represent a MDP problem.
	*/
	class MDP;
	
	
	/**
          \class    MDPDistribution
          \brief 	Interface of a MDP distribution.
	*/
	class MDPDistribution;
	
	
	/**
          \class    DirMultiDistribution
          \brief 	A MDP distribution represented by a Dirichlet Multinomial
	               distribution.
	*/
	class DirMultiDistribution;
	
	
	/**
          \class    Model
          \brief 	Interface of a model of a MDP.
	*/
	class Model;
	
	
	/**
          \class    CModel
          \brief 	A Model represented by a set of counters.
	*/
	class CModel;

     
     /**
          \class    Experiment
          \brief 	Represent a RL experiment.
     */
	class Experiment;


	// ======================================================================
	//	Namespaces
	// ======================================================================
	/**
		\brief	This namespace gathers several functions related to
				an RL simulation.
	*/
	namespace simulation
	{
		// =================================================================
		//	Classes
		// =================================================================
		/**
			\brief	Represent a transition observed during the
					interaction between an Agent and a MDP.
		*/
		typedef rl_utils::simulation::
			Transition<unsigned int, unsigned int, double> Transition;


		/**
			\brief	Represent the data gathered during the interaction
					between an Agent and a MDP over a single trajectory.
		*/
		typedef rl_utils::simulation::
			SimulationRecord<unsigned int, unsigned int, double>
					SimulationRecord;
		
		
		// =================================================================
		//	Functions
		// =================================================================
		/**
			\brief		Perform a single trajectory simulation.
			
			\param[agent	The agent interacting with the MDP.
			\param[mdp	The MDP representing the environment.
			\param[gamma	The discount factor.
			\param[T		The horizon limit.
			\param[safeSim	If true, the MDP is 'unknown', preventing the
						agent to access MDP data
						(e.g.: the transition matrix).
			
			\return		A SimulationRecord storing all the data
						about the simulation performed.
		*/
		simulation::SimulationRecord
				simulate(	dds::Agent* agent, dds::MDP* mdp,
						double gamma, unsigned int T,
						bool safeSim = true)
                                        throw (AgentException, MDPException);
	}
	
	
	/**
		\brief	This namespace gathers OPPS algorithms:
					-	OPPS-UCB1	(for discrete strategy spaces)
					-	OPPS-UCT	(for continuous strategy spaces)
	*/
	namespace opps
	{
	     /**
		     \brief    A StoSOO instance where evaluating the function 'f'
		               consists to test the strategy represented by the
		               center vector of parameters of the part of the domain
		               represented by the node, and play it on a MDP of the
		               given MDP distribution.
		*/
		class StoSOO : public utils::algorithm::StoSOO
		{
			public:
			     // =======================================================
			     //     Public Constructors.
			     // =======================================================
                    /**
                         \brief               Constructor.

                         \param[K             The arity of the tree to develop
                                              (odd number).
			          \param[k             The maximal number of evaluations
			                               per node.
			          \param[hMax          The maximal depth of the tree to
			                               develop.
			          \param[delta         The confidence parameter.
                         \param[agentFactory_ The AgentFactory to use for
                                              bulding the strategies.
                         \param[mdpDistrib_   The MDP distribution from to
                                              learn.
                         \param[gamma_        The discount factor.
                         \param[T_            The horizon limit.
                    */
				StoSOO(unsigned int K,
                           unsigned int k, unsigned int hMax, double delta,
				       AgentFactory* agentFactory_,
					  const MDPDistribution* mdpDistrib_,
					  double gamma_, unsigned int T_);


			private:
			     // =======================================================
			     //     Private attributes.
			     // =======================================================
			     /**
                         \brief    The AgentFactory to use for bulding the
                                   strategies.
			     */
				AgentFactory* agentFactory;
				
				
				/**
				     \brief     The MDP distribution from to learn.
				*/
				const MDPDistribution* mdpDistrib;
				
				
				/**
				     \brief     The discount factor.
				*/
				double gamma;
				
				
				/**
				     \brief     The horizon limit.
				*/
				unsigned int T;
				
				
				// =======================================================
			     //     Private methods.
			     // =======================================================
				/**
                         \brief    Represent the function to optimize.
                                   Return a noisy evaluation of 'f' in 'x'.
          
                         \param[x  The point in which to evaluate 'f'.
          
                         \return   A noisy evaluation of 'f' in 'x'.
          		*/
          		double f(const std::vector<double>& x) const
                                                       throw (std::exception);
		};

	    
          /**
               \brief    A UCB1 instance where drawing an arm consists to play
                         the associated strategy an a MDP of the given MDP
                         distribution.
          */	
		class UCB1 : public utils::algorithm::UCB1
		{
			public:
			     // =======================================================
			     //     Public Constructor.
			     // =======================================================
                    /**
                         \brief               Constructor.
                         
                         \param[c             The constant used in the UCB1
                                              formula:
                                                 I_t(i) =
                                                 mu_i + c * sqrt(ln(n_t) / n_i)
                         \param[strategyList_ The list of strategies.
                         \param[mdpDistrib_   The MDP distribution from to
                                              learn.
                         \param[gamma_        The discount factor.
                         \param[T_            The horizon limit.
                    */
				UCB1(double c,
					const vector<Agent*>& strategyList_,
					const MDPDistribution* mdpDistrib_,
					double gamma_, unsigned int T_);

			private:
			     // =======================================================
			     //     Private attributes.
			     // =======================================================
                    /**
                         \brief    The list of strategies.
                    */
				const vector<Agent*>& strategyList;
			
				
				/**
				     \brief     The MDP distribution from to learn.
				*/
				const MDPDistribution* mdpDistrib;
				
				
				/**
				     \brief     The discount factor.
				*/
				double gamma;
				
				
				/**
				     \brief     The horizon limit.
				*/
				unsigned int T;
				
				
				// =======================================================
				//    Private methods.
				// =======================================================
				/**
          			\brief	Draw the arm 'i' and return its score.
          			
          			\param[i	The arm to draw.
          		*/
				double drawArm(unsigned int i) const
                                                       throw (std::exception);
		};

          
          /**
		     \brief    A UCT instance where drawing an arm from a node
		               consists to draw a strategy from the part of the
		               strategy space defined by this node, and play it on
		               a MDP of the given MDP distribution.
		*/
		class UCT : public utils::algorithm::UCT
		{
			public:
			     // =======================================================
			     //     Public Constructor.
			     // =======================================================
                    /**
                         \brief               Constructor.
                         
                         \param[c             The constant used in the UCB1
                                              formula:
                                                 I_t(i) =
                                                 mu_i + c * sqrt(ln(n_t) / n_i)
                         \param[agentFactory_ The AgentFactory to use for
                                              bulding the strategies.
                         \param[mdpDistrib_   The MDP distribution from to
                                              learn.
                         \param[gamma_        The discount factor.
                         \param[T_            The horizon limit.
                    */
				UCT(	double c,
					AgentFactory* agentFactory_,
					const MDPDistribution* mdpDistrib_,
					double gamma_, unsigned int T_);

			private:
			     // =======================================================
			     //     Private attributes.
			     // =======================================================
			     /**
                         \brief    The AgentFactory to use for bulding the
                                   strategies.
			     */
				AgentFactory* agentFactory;
				
				
				/**
				     \brief     The MDP distribution from to learn.
				*/
				const MDPDistribution* mdpDistrib;
				
				
				/**
				     \brief     The discount factor.
				*/
				double gamma;
				
				
				/**
				     \brief     The horizon limit.
				*/
				unsigned int T;
				
				
				// =======================================================
			     //     Private methods.
			     // =======================================================
				/**
          			\brief			Draw the arm defined by
          			                    'paraSList' and return its score.
          			
          			\param[paraSList	The parameters defining the arm to
          			                    draw.
          			
          			\return			The score of the arm defined by
          			                    'paraSList'.
          		*/
				double drawArm(const vector<double>& paraSList) const
                                                       throw (std::exception);
		};
	}
}

#endif
