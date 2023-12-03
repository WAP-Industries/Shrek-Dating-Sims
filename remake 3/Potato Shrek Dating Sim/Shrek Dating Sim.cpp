#include "Potato.hpp" 

// character
Potato::Character Shrek("Shrek Senpai", 0,0,300,400, {"assets/characters/shrek.png"});
Potato::Character Explosion("", 0,0,400,400, {"assets/characters/explosion.png"});
Potato::Character Knuckles("Knuckles", 0,0,400,400, {"assets/characters/knuckles.png"});


void SetUp(Potato::Engine& Engine){
    Engine.SetFont("assets/misc/vt323.ttf");
    Engine.SetTitleScreen("Can't Get Ogre You", 80, "assets/misc/startscreen.png");
    Engine.Scene.SetTransition(Potato::Transitions::FadeInOut);

    Engine.UI.DialogueBox.FontSize*=1.5;
    Engine.UI.NameBox.FontSize*=1.5;
    Engine.UI.DialogueBox.Background = std::make_tuple(255, 192, 203);
}
 
int main(){ 
    Potato::Init();

    // audio
    Potato::Audio Boom("assets/audio/vine_boom.wav");
    Potato::Audio Pipe("assets/audio/lead_pipe.wav");

    Potato::Engine engine("Shrek Dating Sim");
    SetUp(engine);

    // pedo frames
    std::vector<std::string> PedoFrames;
    for (int i=1;i<=16;i++)
        PedoFrames.push_back("assets/characters/pedo (" + std::to_string(i) +  ").png");

    auto Appear = [&](Potato::Character& Char)->void{
        Char.Opacity = 0;
        Potato::Effects::FadeIn(Char);
        Potato::Effects::Slide(Char, (engine.ScreenWidth-Char.Width)/2, 0);
    };

    auto Choice = [&](int s1, int s2){
        engine.Scene.Choice(
            {
                Potato::Choice("Yes", s1, std::make_tuple(255, 255, 255), std::make_tuple(0,0,0), 30),
                Potato::Choice("No", s2, std::make_tuple(255, 255, 255), std::make_tuple(0,0,0), 30)
            }
        );
    };

    engine.SetStory({ 

        // endings
        {
            0, [&](){
                engine.End({"Game Over"});
            }
        },
        {
            -1, [&](){
                engine.End(
                    {
                        "From that day onwards, Shrek Senpai didn't talk to me again.", 
                        "Game Over"
                    }
                );
            }
        },
        {
            -2, [&](){
                engine.End(
                    {
                        "You died from the cringe.",
                        "Game Over"
                    }
                );
            }
        },

        {
            1, [&](){
                Potato::Threading::RunAsync(
                    [&](){
                        Potato::Threading::Delay(1000);
                        engine.Scene.SetBackgroundImage("assets/backgrounds/hallway.png");

                        Potato::Threading::Delay(2000);
                        engine.Scene.AddCharacter(&Shrek);
                        Shrek.X = (engine.ScreenWidth-Shrek.Width)/2;
                        Potato::Effects::FadeIn(Shrek);

                        engine.Scene.Speak(NULL, "(I've been watching Senpai from afar for so long...)");
                        engine.Scene.ClearTransition();
                    }
                );
                engine.Step(1);
            }
        },
        {
            2, [&](){
                engine.Scene.Speak(NULL, "Should I confess to her now?");
                engine.Step(1);
            }
        },
        {
            3, [&](){
                Choice(4, 7);
            }
        },

        // hallway rejection route
        {
            4, [&](){
                engine.Scene.Speak(NULL, "Senpai!! I like you!!");
                engine.Step(1);
            }
        },
        {
            5, [&](){
                engine.Scene.Speak(NULL, "(Shit, everyone's staring at me...)");
                engine.Step(1);
            }
        },
        {
            6, [&](){
                Shrek.Images = {"assets/characters/angry_shrek.png"};
                engine.Scene.Speak(&Shrek, "GET AWAY FROM ME BAKA!!!!");
                Boom.Play();
                engine.Jump(0);
            }
        },

        // back to normal route
        {
            7, [&](){
                engine.Scene.Speak(NULL, "Senpai, can we talk in private somewhere else?");
                engine.Step(1);
            }
        },
        {
            8, [&](){
                engine.Scene.Speak(&Shrek, "Sure!");
                engine.Scene.SetTransition(Potato::Transitions::FadeInOut);
                engine.Step(1);
            }
        },
        {
            9, [&](){
                Potato::Threading::RunAsync(
                    [&](){
                        Potato::Threading::Delay(1000);
                        Shrek.Opacity = 0;
                        engine.Scene.SetBackgroundImage("assets/backgrounds/courtyard.png");

                        Potato::Threading::Delay(2000);
                        Shrek.X = 0;
                        Appear(Shrek);

                        engine.Scene.Speak(NULL, "*You bring Shrek to the school courtyard.*");
                        engine.Scene.ClearTransition();
                    }
                );
                engine.Step(1);
            }
        },
        {
            10, [&](){
                engine.Scene.Speak(NULL, "Senpai... I like you!!!");
                engine.Step(1);
            }
        },
        {
            11, [&](){
                engine.Scene.Speak(&Shrek, "...!");
                engine.Step(1);
            }
        },
        {
            12, [&](){
                engine.Scene.Speak(&Shrek, "I like you too!!");
                engine.Step(1);
            }
        },
        {
            13, [&](){
                engine.Scene.Speak(&Shrek, "But I'm too ugly for you...");
                engine.Step(1);
            }
        },
        {
            14, [&](){
                engine.Scene.Speak(NULL, "That's not true, you're really pretty!");
                engine.Step(1);
            }
        },
        {
            15, [&](){
                engine.Scene.Speak(&Shrek, "I'm so happy...");
                engine.Step(1);
            }
        },
        {
            16, [&](){
                engine.Scene.Speak(&Shrek, "But I just wish I could be human again.");
                engine.Step(1);
            }
        },
        {
            17, [&](){
                engine.Scene.Speak(&Shrek, "You see, I was turned into an ogre by an evil wizard, Joe M. Ligma...");
                engine.Step(1);
            }
        },
        {
            18, [&](){
                engine.Scene.Speak(&Shrek, "And the only way to reverse the curse is by eating the Ligma fruit!");
                engine.Step(1);
            }
        },
        {
            19, [&](){
                engine.Scene.Speak(&Shrek, "Will you help me get the Ligma fruit?");
                engine.Step(1);
            }
        },
        {
            20, [&](){
                Choice(24, 21);
            }
        },

        // reject fruit route
        {
            21, [&](){
                engine.Scene.Speak(NULL, "Nah, I think I'll pass.");
                engine.Step(1);
            }
        },
        {
            22, [&](){
                engine.Scene.Speak(&Shrek, "Oh, okay then...");
                engine.Step(1);
            }
        },
        {
            23, [&](){
                Boom.Play();
                engine.Scene.Speak(NULL, "Shrek senpai ran away with tears in her eyes.");
                Potato::Effects::FadeOut(Shrek);
                Potato::Effects::Slide(Shrek, engine.ScreenWidth, 0);
                engine.Jump(-1);
            }
        },

        // back to normal route
        {
            24, [&](){
                engine.Scene.Speak(NULL, "Sure! I'll do it for senpai!");
                engine.Step(1);
            }
        },
        {
            25, [&](){
                engine.Scene.Speak(&Shrek, "Thank you so much! You can find the Ligma fruit on Goteem Island!");
                engine.Scene.SetTransition(Potato::Transitions::FadeInOut);
                engine.Step(1);
            }
        },
        {
            26, [&](){
                Potato::Threading::RunAsync(
                    [&](){
                        Potato::Threading::Delay(1000);
                        Shrek.Opacity = 0;
                        engine.Scene.SetBackgroundImage("assets/backgrounds/cave.png");

                        Potato::Threading::Delay(2000);
                        engine.Scene.Speak(NULL, "*Later that day, you head to Goteem island, in search of the Ligma fruit.*");

                        engine.Scene.ClearTransition();
                    }
                );
                engine.Step(1);
            }
        },
        {
            27, [&](){
                engine.Scene.Speak(NULL, "Sheesh, this place is big!");
                engine.Step(1);
            }
        },
        {
            28, [&](){
                engine.Scene.AddCharacter(&Knuckles);
                engine.Scene.Speak(&Knuckles, "What brings you here my child?");
                Appear(Knuckles);
                engine.Step(1);
            }
        },
        {
            29, [&](){
                engine.Scene.Speak(NULL, "I'm here to find the Ligma fruit. Who are you?");
                engine.Step(1);
            }
        },
        {
            30, [&](){
                engine.Scene.Speak(
                    &Knuckles, 
                    "I am the guardian of the Ligma fruit, I only give it to those I deem worthy,"
                    "to prevent it from falling into the wrong hands."
                );
                engine.Step(1);
            }
        },
        {
            31, [&](){
                engine.Scene.Speak(
                    &Knuckles, 
                    "If you seek the Ligma fruit, you must answer a question. Failure will result in death."
                );
                engine.Step(1);
            }
        },
        {
            32, [&](){
                engine.Scene.Speak(NULL, "Alright then, bring it on!");
                engine.Step(1);
            }
        },
        {
            33, [&](){
                engine.Scene.Speak(&Knuckles, "Do you know Candice?");
                engine.Step(1);
            }
        },
        {
            34, [&](){
                Choice(37, 35);
            }
        },

        // deez nuts death route
        {
            35, [&](){
                engine.Scene.Speak(NULL, "Uh... no...?");
                engine.Step(1);
            }
        },
        {
            36, [&](){
                Boom.Play();
                engine.Scene.Speak(&Knuckles, "CANDEEZ NUTS FIT IN YO MOUTH");
                engine.Jump(-2);
            }
        },

        // back to normal route
        {
            37, [&](){
                engine.Scene.Speak(NULL, "Yes...?");
                engine.Step(1);
            }
        },
        {
            38, [&](){
                engine.Scene.Speak(&Knuckles, "It seems, you ARE worthy.");
                engine.Step(1);
            }
        },
        {
            39, [&](){
                engine.Scene.Speak(&Knuckles, "As promised, here's a Ligma fruit.");
                engine.Step(1);
            }
        },
        {
            40, [&](){
                engine.Scene.Speak(NULL, "*Knuckles places a weird-looking fruit into your hand.*");
                engine.Step(1);
            }
        },
        {
            41, [&](){
                engine.Scene.Speak(NULL, "Thanks foo.");
                engine.Scene.SetTransition(Potato::Transitions::FadeInOut);
                engine.Step(1);
            }
        },
        {
            42, [&](){
                Potato::Threading::RunAsync(
                    [&](){
                        Potato::Threading::Delay(1000);
                        engine.Scene.SetBackgroundImage("assets/backgrounds/courtyard.png");
                        engine.Scene.RemoveCharacter(&Knuckles);

                        Potato::Threading::Delay(2000);
                        Potato::Effects::FadeIn(Shrek);

                        engine.Scene.Speak(NULL, "*You meet Shrek Senpai in school the next day.*");
                        engine.Scene.ClearTransition();
                    }
                );
                engine.Step(1);
            }
        },
        {
            43, [&](){
                engine.Scene.Speak(NULL, "Senpai, I found the Ligma fruit!");
                engine.Step(1);
            }
        },
        {
            44, [&](){
                engine.Scene.Speak(&Shrek, "I knew you could do it!!");
                engine.Step(1);
            }
        },
        {
            45, [&](){
                engine.Scene.Speak(NULL, "*You give the Ligma fruit to Shrek Senpai, who eats it in one gobble.*");
                engine.Step(1);
            }
        },
        {
            46, [&](){
                Shrek.Images.push_back("assets/characters/blank.png");
                engine.Scene.Speak(NULL, "*Shrek Senpai begins to change!*");
                engine.Step(1);
            }
        },
        {
            47, [&](){
                Shrek.Images = {"assets/characters/shadow.png"};
                engine.Scene.AddCharacter(&Explosion);
                Explosion.X = (engine.ScreenWidth-Explosion.Width)/2;
                Pipe.Play();
                engine.Scene.Speak(NULL, "SENPAI!!!");
                engine.Step(1);
            }
        },
        {
            48, [&](){
                engine.Scene.Speak(&Shrek, "It's alright, I'm fine!");
                engine.Step(1);
            }
        },
        {
            49, [&](){
                Potato::Threading::RunAsync(
                    [&](){
                        while (Explosion.Opacity>0){
                            Explosion.Opacity-=0.05;
                            Potato::Threading::Delay(100);
                        }
                    }
                );
                engine.Scene.Speak(NULL, "*As the smoke clears, you see that Shrek Senpai has changed!*");
                engine.Step(1);
            }
        },
        {
            50, [&](){
                Boom.Play();
                engine.Scene.RemoveCharacter(&Explosion);

                Shrek.Images = PedoFrames;
                Shrek.FrameRate = 2;
                Shrek.X = Shrek.Y = 0;
                Shrek.Width = engine.ScreenWidth;
                Shrek.Height = engine.ScreenHeight;
                
                engine.Scene.Speak(&Shrek, "This is my true form!");
                engine.Step(1);
            }
        },
        {
            51, [&](){
                engine.Scene.Speak(&Shrek, "Shall we go on a date now?");
                engine.Step(1);
            }
        },
        {
            52, [&](){
                engine.Scene.Speak(NULL, "wtf");
                engine.Step(1);
            }
        },
        {
            53, [&](){
                engine.End({"Game End!"});
            }
        }
    }); 
    engine.Jump(1);
    engine.Run(); 
    return 0; 
} 
