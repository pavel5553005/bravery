#ifndef Texture_hpp_
#define Texture_hpp_

class Texture
{
public:
    struct Pixel
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

private:
    
public:
    Texture(int width, int height);
    ~Texture();
};

Texture::Texture(int width, int height)
{
}

Texture::~Texture()
{
}


#endif