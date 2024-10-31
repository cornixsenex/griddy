#define TEXTURE_NONE 0

#define TEXTURE_FIELD_NUM1 1
#define TEXTURE_FIELD_NUM2 2
#define TEXTURE_FIELD_NUM3 3
#define TEXTURE_FIELD_NUM4 4
#define TEXTURE_FIELD_NUM5 5

#define TEXTURE_FIELD_NUM0 10

#define TEXTURE_COUNT 7

extern SDL_Texture* textures[TEXTURE_COUNT];

void LoadFieldTextures();
void DestroyFieldTextures();
