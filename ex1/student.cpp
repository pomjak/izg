/**
 * IZG - Zaklady pocitacove grafiky - FIT VUT
 * Lab 01 - Redukce barevneho prostoru
 *
 * Copyright (c) 2022-23 by Michal Vlnas, ivlnas@fit.vutbr.cz
 *
 * Tato sablona slouzi vyhradne pro studijni ucely, sireni kodu je bez vedomi autora zakazano.
 */

#include "base.h"
using namespace std;

/**
 * Converts image into grayscale.
 * Use empiric equation presented in lecture.
 */
void ImageTransform::grayscale()
{
    // TODO: write code here
    RGB px;
    for (uint32_t x = 0; x < cfg->w; x++)
        for (uint32_t y = 0; y < cfg->h; y++)
        {
            px = getPixel(x,y);
            setPixel(x,y,std::round(0.299*px.r + 0.587 * px.g + 0.114*px.b));
        }
            
}

/**
 * Evaluate threshold value for further usage in thresholding,
 * has to be called after grayscale().
 *
 * Note: evaluation method will DIFFER for each group!
 *
 * @return threshold
 */
uint8_t ImageTransform::evaluateThreshold()
{
    uint8_t th = 128;
    uint32_t cnt = 0;
    // TODO: write code here or in evaluateThreshold(x, y)
    uint32_t sum = 0;
    for (uint32_t y = 0; y < cfg->h; y++)
    {
        for (uint32_t x = 0; x < cfg->w; x++)
        {
            if(!(x%2))
            {
                auto px = getPixel(x, y);
                sum += px.r;
                cnt++;
            }
        }
    }
    th = uint8_t(sum/cnt);
    IZG_INFO("Evaluated threshold: " + std::to_string(th));
    return th;
}

/**
 * Evaluate threshold value for further usage in thresholding,
 * has to be called after grayscale().
 *
 * Note: evaluation method will DIFFER for each group!
 *
 * @param x Input pixel coordinate
 * @param y Input pixel coordinate
 * @return  threshold
 */
uint8_t ImageTransform::evaluateThreshold(int32_t x, int32_t y)
{
    (void)x;
    (void)y;

    uint8_t th = 128;

    // TODO: write code here or in evaluateThreshold()
    return th;
}

void ImageTransform::threshold()
{
    // TODO: write code here
    grayscale();
    uint8_t th = evaluateThreshold();
    for (uint32_t y = 0; y < cfg->h; y++)
    {
        for (uint32_t x = 0; x < cfg->w; x++)
        {
            auto p = getPixel(x, y);
            uint8_t value = p.r > th ? 255 : 0;

            setPixel(x, y, RGB(value));
        }
    }
}

void ImageTransform::randomDithering()
{
    grayscale();

    for (uint32_t y = 0; y < cfg->h; y++)
    {
        for (uint32_t x = 0; x < cfg->w; x++)
        {
            auto p = getPixel(x, y);
            uint8_t value = p.r > getRandom() ? 255 : 0;

            setPixel(x, y, RGB(value));
        }
    }
}

void ImageTransform::orderedDithering()
{
    static uint8_t matrix[m_side][m_side] =
    {
        { 0,   254, 51,  255 },
        { 68,  136, 187, 119 },
        { 34,  238, 17,  221 },
        { 170, 102, 153, 85  }
    };

    // TODO: write code here
    grayscale();
    for (uint32_t y = 0; y < cfg->h; y++)
    {
        for (uint32_t x = 0; x < cfg->w; x++)
        {
            auto p = getPixel(x, y);
            auto value = p.r > matrix[x%m_side][y%m_side] ? COLOR_WHITE : COLOR_BLACK;

            setPixel(x, y, RGB(value));
        }
    }
}

void ImageTransform::updatePixelWithError(uint32_t x, uint32_t y, float err)
{
    (void)x;
    (void)y;
    (void)err;

    // TODO: write code here
    auto px = getPixel(x,y);
    int color = round(px.r + err);

    if(err < 0) color = std::max(color,0);
    else color = std::min(color,255);

    setPixel(x,y,RGB(color));
}

void ImageTransform::errorDistribution()
{
    // TODO: write code here
    float err;
    grayscale();
    uint8_t th = evaluateThreshold();

    for (uint32_t y = 0; y < cfg->h; y++)
    {
        for (uint32_t x = 0; x < cfg->w; x++)
        {
            auto p = getPixel(x, y);
            if(p.r > th )
            { 
                err = p.r - COLOR_WHITE.r;
                setPixel(x,y,COLOR_WHITE);
            }
            else 
            {
                err = p.r;
                setPixel(x, y, COLOR_BLACK);
            }

            if (x <cfg->w - 1)
                updatePixelWithError(x + 1, y, err * 3 / 8);
            if(y < cfg->h -1)
                updatePixelWithError(x, y + 1, err * 3 / 8);
            if (x < cfg->w - 1 &&y < cfg->h - 1)
                updatePixelWithError(x + 1, y + 1, err * 2 / 8);
        }
    }
}

