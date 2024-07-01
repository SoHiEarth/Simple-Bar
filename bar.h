#pragma once
#include <iostream>
#include <string>

// Customizable values, adjust to liking.
int DEFAULT_TITLE_LENGTH                = 5;      // Default is 5
std::string DEFAULT_CONTENT_CHARACTER   = "=";    // Default is "="
std::string DEFAULT_SPACER_CHARACTER    = " ";    // Default is " "
std::string DEFAULT_END_CHARACTER       = "\n";   // Default is "\n"
std::string DEFAULT_EOL_CHARACTER       = "\r";   // Default is "\r"

struct Bar
{
   std::string TITLE;
   int PROGRESS;

   bool TRUNCATE_TITLES                 = true;   // Truncates titles to MAX_TITLE_LENGTH letters.
   bool APPEND_PERCENTAGE               = true;   // Append the percentage in numerical and non-numeral modes.
   bool SHOW_TITLE                      = true;   // Show the title in numerical and non-numeral modes.
   bool SHOW_CONTENT                    = true;   // Show the content in non-numeral modes.
   bool NUMERAL_MODE                    = false;  // Numeral mode is a simplified mode that displays minimal information.

   int MAX_TITLE_LENGTH;
   std::string CONTENT_CHARACTER        = DEFAULT_CONTENT_CHARACTER;
   std::string SPACER_CHARACTER         = DEFAULT_SPACER_CHARACTER;
   std::string END_CHARACTER            = DEFAULT_END_CHARACTER;
   std::string EOL_CHARACTER            = DEFAULT_EOL_CHARACTER;

   int CUSTOM_TITLE_LENGTH;                     // To nullify, set to 0
   std::string CUSTOM_CONTENT_CHARACTER = "";   // To nullify, set to ""
   std::string CUSTOM_SPACER_CHARACTER  = "";   // To nullify, set to ""
   std::string CUSTOM_END_CHARACTER     = "";   // To nullify, set to ""
   std::string CUSTOM_EOL_CHARACTER     = "";   // To nullify, set to ""
};

enum BAR_FLAGS
{
   BAR_INIT_CORE,   // Initialize only core components
   BAR_INIT_SAFE,   // Initialize only the minimum components
   BAR_INIT,        // Initialize the manager
   BAR_QUIT_CORE,   // Quit only the core components (rare)
   BAR_QUIT         // Quit bar manager
};

namespace BarMan
{
   int Initialize(Bar* bar, BAR_FLAGS FLAG)
   {
      bar->MAX_TITLE_LENGTH  = (bar->CUSTOM_TITLE_LENGTH == 0)       ? DEFAULT_TITLE_LENGTH      : bar->CUSTOM_TITLE_LENGTH;        // Configure MAX_TITLE_LENGTH
      bar->CONTENT_CHARACTER = (bar->CUSTOM_CONTENT_CHARACTER == "") ? DEFAULT_CONTENT_CHARACTER : bar->CUSTOM_CONTENT_CHARACTER;   // Configure CONTENT_CHARACTER
      bar->SPACER_CHARACTER = (bar->CUSTOM_SPACER_CHARACTER == "")  ? DEFAULT_SPACER_CHARACTER  : bar->CUSTOM_SPACER_CHARACTER;    // Configure SPACER_CHARACTER
      bar->END_CHARACTER     = (bar->CUSTOM_END_CHARACTER == "")     ? DEFAULT_END_CHARACTER     : bar->CUSTOM_END_CHARACTER;       // Configure END_CHARACTER
      bar->EOL_CHARACTER     = (bar->CUSTOM_EOL_CHARACTER == "")     ? DEFAULT_EOL_CHARACTER     : bar->CUSTOM_EOL_CHARACTER;       // Configure EOL_CHARACTER
      return 0;
   }

   int Quit(Bar* bar, BAR_FLAGS FLAG)
   {
      bar->CONTENT_CHARACTER = "";
      bar->SPACER_CHARACTER  = "";
      bar->END_CHARACTER     = "";
      bar->EOL_CHARACTER     = "";
      bar->MAX_TITLE_LENGTH  = 0;
      return 0;
   }
}

void UpdateBar(Bar* bar)
{
   #ifdef NDEBUG // If release do not output logs
   return;
   #else
   if (bar->TRUNCATE_TITLES)
   {
      // Strip bar to MAX_TITLE_LENGTH letters
      if (bar->TITLE.length() > bar->MAX_TITLE_LENGTH)
      {
         bar->TITLE = "(...)";
      }

      if (bar->TITLE.length() < bar->MAX_TITLE_LENGTH)
      {
         int o = bar->MAX_TITLE_LENGTH - bar->TITLE.length();
         int i = 0;

         while (i < o)
         {
            bar->TITLE += DEFAULT_SPACER_CHARACTER;
            i++;
         }
      }
   }

   // Normal bar mode
   if (!bar->NUMERAL_MODE && bar->SHOW_CONTENT)
   {
      // Start Bar
      if (bar->SHOW_TITLE) std::cout << "[ " << bar->TITLE << " ] [ ";
      else std::cout << "[ ";

      // Actual contents
      if (bar->PROGRESS <= 100)
      {
         for (int i = 0; i < bar->PROGRESS; i++)
         {
               std::cout << bar->CONTENT_CHARACTER;
         }

         for (int i = 0; i < 100 - bar->PROGRESS; i++)
         {
               std::cout << bar->SPACER_CHARACTER;
         }
      }

      // End bar, if last out newline.
      if (bar->APPEND_PERCENTAGE)
      {
         if (bar->PROGRESS < 100) std::cout << " ] " << bar->PROGRESS << "%" << bar->EOL_CHARACTER;
         if (bar->PROGRESS >= 100) std::cout << " ] " << bar->PROGRESS << "%" << bar->END_CHARACTER;
      }
      else
      {
         if (bar->PROGRESS < 100) std::cout << " ]" << bar->EOL_CHARACTER;
         if (bar->PROGRESS >= 100) std::cout << " ]" << bar->END_CHARACTER;
      }
   }

   if (bar->NUMERAL_MODE)
   {
      if (bar->SHOW_TITLE) std::cout << bar->TITLE << ", ";
      if (bar->APPEND_PERCENTAGE)
      {
         if (bar->PROGRESS < 100) std::cout << "Progress: " << bar->PROGRESS << "%" << bar->EOL_CHARACTER;
         if (bar->PROGRESS >= 100) std::cout << "Progress: " << bar->PROGRESS << "%" << bar->END_CHARACTER;
      }
   }
   return;
   #endif
}

// Utilities that are not required to execute, but still are nice to have
namespace BarUtils 
{
   // Fill this out and pass it to the InitializeBar utility to easily create a bar.
   struct BarInitForm
   {
      std::string title;
      int startProgress;

      bool TRUNCATE_TITLES                 = true;    // Truncates titles to MAX_TITLE_LENGTH letters.
      bool APPEND_PERCENTAGE               = true;    // Append the percentage in numerical and non-numeral modes.
      bool SHOW_TITLE                      = true;    // Show the title in numerical and non-numeral modes.
      bool SHOW_CONTENT                    = true;    // Show the content in non-numeral modes.
      bool NUMERAL_MODE                    = false;   // Numeral mode is a simplified mode that displays minimal information.

      int MAX_TITLE_LENGTH;
      std::string CONTENT_CHARACTER        = DEFAULT_CONTENT_CHARACTER;
      std::string SPACER_CHARACTER         = DEFAULT_SPACER_CHARACTER;
      std::string END_CHARACTER            = DEFAULT_END_CHARACTER;
      std::string EOL_CHARACTER            = DEFAULT_EOL_CHARACTER;

      int CUSTOM_TITLE_LENGTH;                     // To nullify, set to 0
      std::string CUSTOM_CONTENT_CHARACTER = "";   // To nullify, set to ""
      std::string CUSTOM_SPACER_CHARACTER  = "";   // To nullify, set to ""
      std::string CUSTOM_END_CHARACTER     = "";   // To nullify, set to ""
      std::string CUSTOM_EOL_CHARACTER     = "";   // To nullify, set to ""
   };

   Bar* Initialize(BarInitForm form)
   {
      Bar* bar                 = new Bar;
      bar->PROGRESS            = form.startProgress;
      bar->TITLE               = form.title;
      bar->TRUNCATE_TITLES     = form.TRUNCATE_TITLES;
      bar->APPEND_PERCENTAGE   = form.APPEND_PERCENTAGE;
      bar->SHOW_TITLE          = form.SHOW_TITLE;
      bar->SHOW_CONTENT        = form.SHOW_CONTENT;
      bar->MAX_TITLE_LENGTH    = (form.CUSTOM_TITLE_LENGTH == 0)       ? DEFAULT_TITLE_LENGTH      : form.CUSTOM_TITLE_LENGTH;
      bar->CONTENT_CHARACTER   = (form.CUSTOM_CONTENT_CHARACTER == "") ? DEFAULT_CONTENT_CHARACTER : form.CUSTOM_CONTENT_CHARACTER;
      bar->SPACER_CHARACTER    = (form.CUSTOM_SPACER_CHARACTER == "")  ? DEFAULT_SPACER_CHARACTER  : form.CUSTOM_SPACER_CHARACTER;
      bar->END_CHARACTER       = (form.CUSTOM_END_CHARACTER == "")     ? DEFAULT_END_CHARACTER     : form.CUSTOM_END_CHARACTER;
      bar->EOL_CHARACTER       = (form.CUSTOM_EOL_CHARACTER == "")     ? DEFAULT_EOL_CHARACTER     : form.CUSTOM_EOL_CHARACTER;
      return bar;
   }

   // Free bar from memory
   void DestroyBar(Bar* bar)
   {
      delete(bar);
   }

   // Increment the bar's progress by incrementLevel.
   void IncrementProgress(Bar* bar, int incrementLevel = 1)
   {
      bar->PROGRESS += incrementLevel;
   }

   // Decrement the bar's progress by decrementLevel.
   void DecrementProgress(Bar* bar, int decrementLevel = 1)
   {
      bar->PROGRESS -= decrementLevel;
   }
}