#include <uikit/text.h>

UIText* UIText_Create(char* text, float fontSize) {
    UIText* uiText = (UIText*)malloc(sizeof(UIText));
    if (uiText == NULL) {
        fprintf(stderr, "Failed to allocate memory for UIText\n");
        return NULL; // Memory allocation failed
    }

    if (text == NULL) {
        text = _strdup(""); // Default text if NULL
    }

    uiText->marginBottom = 0;
    uiText->marginLeft = 0;
    uiText->marginRight = 0;
    uiText->marginTop = 0;
    uiText->paddingBottom = 0;
    uiText->paddingLeft = 0;
    uiText->paddingRight = 0;
    uiText->paddingTop = 0;

    uiText->fontSize = fontSize;
    uiText->fontFamily = _strdup(DEFAULT_FONT_PATH); // Default font family
    uiText->fontStyle = Normal; // Default style
    uiText->color = UI_COLOR_BLACK; // Default color (black)
    UIRectangle* UIRecN = UIRectangle_Create(); // Default rectangle
    UIRectangle_SetColor(UIRecN, UI_COLOR_TRANSPARENT); // Set default color (white)

    uiText->background = UIRecN; // Default background color (white
    uiText->text = _strdup(text);
    uiText->textLength = strlen(text);
    uiText->__widget_type = UI_WIDGET_TEXT; // Set the widget type
    uiText->__SDL_textTexture = NULL;

    return uiText;
}

UIText* UIText_SetFontFamily(UIText* text, char* fontFamily) {
    if (text == NULL || fontFamily == NULL) {
        return NULL;
    }

    free(text->fontFamily); // Free previous font family
    text->fontFamily = _strdup(fontFamily);
    return text;
}

UIText* UIText_SetFontStyle(UIText* text, int fontStyle) {
    if (text == NULL) {
        return NULL;
    }

    text->fontStyle = fontStyle;
    return text;
}

UIText* UIText_SetColor(UIText* text, UIColor color) {
    if (text == NULL) {
        return NULL; 
    }

    text->color = color;
    return text;
}

UIText* UIText_SetBackground(UIText* text, UIRectangle* backgroundRect) {
    if (text == NULL) {
        return NULL; // Invalid arguments
    }

    free(text->background); // Free previous background color

    if (backgroundRect == NULL) {
        backgroundRect = UIRectangle_Create(); // Default rectangle if NULL
    } else {
        text->background = backgroundRect;
    }
    
    return text;
}

UIText* UIText_SetText(UIText* text, char* newText) {
    if (text == NULL || newText == NULL) {
        return NULL; // Invalid arguments
    }

    if (text->text != NULL) {
        free(text->text); // Free previous text if not NULL
    }
    
    text->text = _strdup(newText);
    text->textLength = strlen(newText);

    // Invalidate the SDL texture if the text changes
    if (text->__SDL_textTexture != NULL) {
        UIText_DestroyTexture(text);
    }
    return text;
}

UIText* UIText_SetMargins(UIText* text, float left, float top, float right, float bottom) {
    if (text == NULL) {
        return NULL; // Invalid argument
    }

    text->marginLeft = left;
    text->marginTop = top;
    text->marginRight = right;
    text->marginBottom = bottom;
    return text;
}

UIText* UIText_SetPadding(UIText* text, float left, float top, float right, float bottom) {
    if (text == NULL) {
        return NULL; // Invalid argument
    }

    text->paddingLeft = left;
    text->paddingTop = top;
    text->paddingRight = right;
    text->paddingBottom = bottom;
    return text;
}

void UIText_DestroyTexture(UIText* text) {
    if (!text || !text->__SDL_textTexture) return;
    SDL_DestroyTexture(text->__SDL_textTexture);
    text->__SDL_textTexture = NULL;
}

void UIText_Destroy(UIText* text) {
    if (text) {
        free(text->fontFamily); 
        free(text->text);
        UIRectangle_Destroy(text->background); 
        UIText_DestroyTexture(text); 
        free(text);
    }
}