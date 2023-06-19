#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int we=state->player;
  auto actions = state->legal_actions;
  int pos=actions.size();
  int lvone=-3000000;
  int bot;
  for(int i=0;i<pos;i++)
  {
    auto postatetwo=state->next_state(actions[i]);
    auto acttwo=postatetwo->legal_actions;
    int postwo=acttwo.size();
    int lvtwo=3000000;
    if(depth<2)
    {
      lvtwo=postatetwo->evaluate(we);
    }
    else
    {
      for(int j=0;j<postwo;j++)
      {
        auto postatethree=postatetwo->next_state(acttwo[j]);
        auto actthree=postatethree->legal_actions;
        int posthree=actthree.size();
        int lvthree=-3000000;
        if(depth<3)
        {
          lvthree=postatethree->evaluate(we);
        }
        else
        {
          for(int k=0;k<posthree;k++)
          {
            auto postatefour=postatethree->next_state(actthree[k]);
            auto actfour=postatefour->legal_actions;
            int posfour=actfour.size();
            int lvfour=3000000;
            if(depth<4)
            {
              lvfour=postatefour->evaluate(we);
            }
            else
            {
              for(int l=0;l<posfour;l++)
              {
                auto postatefive=postatefour->next_state(actfour[l]);
                int lvfive=postatefive->evaluate(we);
                if(lvfive<lvfour)
                {
                  lvfour=lvfive;
                }
              }
            }
            if(lvfour>lvthree)
            {
              lvthree=lvfour;
            }
          }
        }
        
        if(lvthree<lvtwo)
        {
          lvtwo=lvthree;
        }
      }
    }
    
    if(lvtwo>lvone)
    {
      lvone=lvtwo;
      bot=i;
    }
  }
  return actions[bot];
}