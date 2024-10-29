#define TEXTURE_NONE 0

#define TEXTURE_FIELD_NUM3 1

#define TEXTURE_COUNT 2

extern SDL_Texture* textures[TEXTURE_COUNT];

void LoadFieldTextures();
void DestroyFieldTextures();
