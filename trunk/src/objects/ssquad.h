#ifndef SSQUAD_H
#define SSQUAD_H

/*!
 * SSQuad
 * Initialise et affiche un ScreenSpaceQuad pour rendre une texture en plein écran pour le post processing.
 */
class SSQuad
{
public:
    SSQuad();

    void init();
    void draw(unsigned int posIndex);

private:
    static const float vertices[8];
    unsigned int vbuffer;
};

#endif // SSQUAD_H
