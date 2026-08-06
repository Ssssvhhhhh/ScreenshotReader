#include "tesseractengine.h"

TesseractEngine::TesseractEngine()
{
    initialized = (api.Init("tessdata", "rus+eng") == 0);
    api.SetPageSegMode(tesseract::PSM_AUTO);

}

TesseractEngine::~TesseractEngine()
{
    api.End();
}


QString TesseractEngine::imageToText(const QString &path)
{
    if (!initialized)
        return "";

    Pix* pix = pixRead(path.toStdString().c_str());

    if (!pix)
        return "";

    api.SetImage(pix);

    char* text = api.GetUTF8Text();

    QString result = QString::fromUtf8(text);

    delete[] text;
    pixDestroy(&pix);

    return result;
}
