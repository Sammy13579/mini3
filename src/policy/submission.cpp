#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move subAlphabeta::get_move(State *state, int depth){
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
                auto actfive=postatefive->legal_actions;
                int posfive=actfive.size();
                int lvfive=-3000000;
                if(depth<5)
                {
                  lvfive=postatefive->evaluate(we);
                }
                else
                {
                  for(int m=0;m<posfive;m++)
                  {
                    auto postatesix=postatefive->next_state(actfive[m]);
                    auto actsix=postatesix->legal_actions;
                    int possix=actsix.size();
                    int lvsix=3000000;
                    if(depth<6)
                    {
                      lvsix=postatesix->evaluate(we);
                    }
                    else
                    {
                      for(int n=0;n<possix;n++)
                      {
                        auto postateseven=postatesix->next_state(actsix[n]);
                        auto actseven=postateseven->legal_actions;
                        int posseven=actseven.size();
                        int lvseven=-3000000;
                        if(depth<7)
                        {
                          lvseven=postateseven->evaluate(we);
                        }
                        else
                        {
                          for(int o=0;o<posseven;o++)
                          {
                            auto postateeight=postateseven->next_state(actseven[o]);
                            auto acteight=postateeight->legal_actions;
                            int poseight=acteight.size();
                            int lveight=3000000;
                            if(depth<8)
                            {
                              lveight=postateeight->evaluate(we);
                            }
                            else
                            {
                              for(int p=0;p<poseight;p++)
                              {
                                auto postatenine=postateeight->next_state(acteight[p]);
                                int lvnine=postatenine->evaluate(we);
                                if(lvnine<lveight)
                                {
                                  lveight=lvnine;
                                }
                                if(o&&lvnine<=lvseven)
                                {
                                  break;
                                }
                              }
                            }
                            if(lveight>lvseven)
                            {
                              lvseven=lveight;
                            }
                            if(n&&lveight>=lvsix)
                            {
                              break;
                            }
                          }
                        }
                        if(lvseven<lvsix)
                        {
                          lvsix=lvseven;
                        }
                        if(m&&lvseven<=lvfive)
                        {
                          break;
                        }
                      }
                    }
                    if(lvsix>lvfive)
                    {
                      lvfive=lvsix;
                    }
                    if(l&&lvsix>=lvfour)
                    {
                      break;
                    }
                  }
                }
                if(lvfive<lvfour)
                {
                  lvfour=lvfive;
                }
                if(k&&lvfive<=lvthree)
                {
                  break;
                }
              }
            }
            if(lvfour>lvthree)
            {
              lvthree=lvfour;
            }
            if(j&&lvfour>=lvtwo)
            {
              break;
            }
          }
        }
        
        if(lvthree<lvtwo)
        {
          lvtwo=lvthree;
        }
        if(i&&lvthree<=lvone)
        {
          break;
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