#ifndef _RGBCOLOR_
#define _RGBCOLOR_

#include <string>
#include <vector>

typedef struct _RGBColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGBColor;


static enum colorIndex {
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,

	DARK_CORAL,
	DARK_VANILLA,
	DESATURATED_CYAN,
	SUNRAY,
	MOONSTONE_BLUE,
	CITRINE,
	GALAXY_DARK_BLUE,
	GALAXY_REDDISH_PURPLE,
	GALAXY_BLUE_PURPLE,
	GALAXY_PURPLE,
	GALAXY_PINK,
};

static std::vector<std::string> colorName = {
	"White",
	"Black",
	"Basic Red",
	"Basic Green",
	"Basic Blue",

	"Dark Coral",
	"Dark Vanilla",
	"Desaturated Cyan",
	"Sunray",
	"Moonstone Blue",
	"Citrine",
	"GALAXY_DARK_BLUE",
	"GALAXY_REDDISH_PURPLE",
	"GALAXY_BLUE_PURPLE",
	"GALAXY_PURPLE",
	"GALAXY_PINK",
};

static std::vector<RGBColor> colorPallete = {
	{ static_cast<unsigned char>('\255'), static_cast<unsigned char>('\255'), static_cast<unsigned char>('\255') },
	{ static_cast<unsigned char>('\0'), static_cast<unsigned char>('\0'), static_cast<unsigned char>('\0') },
	{ static_cast<unsigned char>('\255'), static_cast<unsigned char>('\0'), static_cast<unsigned char>('\0') },
	{ static_cast<unsigned char>('\0'), static_cast<unsigned char>('\255'), static_cast<unsigned char>('\0') },
	{ static_cast<unsigned char>('\0'), static_cast<unsigned char>('\0'), static_cast<unsigned char>('\255') },

	{ static_cast<unsigned char>('\207'), static_cast<unsigned char>('\79'), static_cast<unsigned char>('\56') },
	{ static_cast<unsigned char>('\221'), static_cast<unsigned char>('\203'), static_cast<unsigned char>('\161') },
	{ static_cast<unsigned char>('\101'), static_cast<unsigned char>('\210'), static_cast<unsigned char>('\147') },
	{ static_cast<unsigned char>('\223'), static_cast<unsigned char>('\184'), static_cast<unsigned char>('\30') },
	{ static_cast<unsigned char>('\117'), static_cast<unsigned char>('\176'), static_cast<unsigned char>('\213') },
	{ static_cast<unsigned char>('\213'), static_cast<unsigned char>('\214'), static_cast<unsigned char>('\0') },


	{ static_cast<unsigned char>('\0'), static_cast<unsigned char>('\7'), static_cast<unsigned char>('\111') },
	{ static_cast<unsigned char>('\167'), static_cast<unsigned char>('\5'), static_cast<unsigned char>('\219') },
	{ static_cast<unsigned char>('\132'), static_cast<unsigned char>('\0'), static_cast<unsigned char>('\255') },
	{ static_cast<unsigned char>('\66'), static_cast<unsigned char>('\7'), static_cast<unsigned char>('\105') },
	{ static_cast<unsigned char>('\255'), static_cast<unsigned char>('\0'), static_cast<unsigned char>('\140') },
};


#endif // !_RGBCOLOR_
