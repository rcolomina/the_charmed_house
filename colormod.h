#ifndef _colormod_
#define _colormod_

#include <ostream>
namespace Color {
     enum Code {
	  /*     FG_RED      = 31,
		 FG_GREEN    = 32,
		 FG_BLUE     = 34,
		 FG_DEFAULT  = 39,
		 BG_RED      = 41,*/
	  FG_DEFAULT = 39,
	  FG_BLACK = 30,
	  FG_RED = 31,
	  FG_GREEN = 32, FG_YELLOW = 33,
	  FG_BLUE = 34, FG_MAGENTA = 35,
	  FG_CYAN = 36, FG_LIGHT_GRAY = 37,
	  FG_DARK_GRAY = 90, FG_LIGHT_RED = 91,
	  FG_LIGHT_GREEN = 92, FG_LIGHT_YELLOW = 93,
	  FG_LIGHT_BLUE = 94, FG_LIGHT_MAGENTA = 95,
	  FG_LIGHT_CYAN = 96, FG_WHITE = 97,
	  BG_RED = 41, BG_GREEN = 42,
	  BG_BLUE = 44, BG_DEFAULT = 49
     };
     
     class Modifier {
	  Code code;
	public:
	  Modifier(Code pCode) : code(pCode) {}
	  friend std::ostream&
	  operator<<(std::ostream& os, const Modifier& mod) {
	       return os << "\033[" << mod.code << "m";
	  }
     };

     static Modifier def(FG_DEFAULT);
     static Modifier black(FG_BLACK);
     static Modifier red(FG_RED);
     static Modifier green(FG_GREEN);
     static Modifier yellow(FG_YELLOW);
     static Modifier blue(FG_BLUE);
     static Modifier magenta(FG_MAGENTA);
     static Modifier cyan(FG_CYAN);
     static Modifier light_gray(FG_LIGHT_GRAY);
     static Modifier dark_gray(FG_DARK_GRAY);
     static Modifier light_red(FG_LIGHT_RED);
     static Modifier light_green(FG_LIGHT_GREEN);
     static Modifier light_yellow(FG_LIGHT_YELLOW);
	 	  
}

#endif
