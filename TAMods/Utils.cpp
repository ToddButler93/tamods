#include "Utils.h"
#include "NameCryptor.h"
#include <Shlobj.h>

namespace Utils
{
    // 60 017504 83295
    UEngine *engine = (UEngine*)(*UObject::GObjObjects())(83295);
    ATrPlayerController *tr_pc = NULL;
    UTrGameViewportClient *tr_gvc = NULL;
    ATrHUD *tr_hud = NULL;
    AUTHUD *ut_hud = UObject::FindObject<AUTHUD>("UTHUD UTGame.Default__UTHUD");
    UGFxTrMenuMoviePlayer *tr_menuMovie = NULL;

    UTexture2D *whiteTexture = UObject::FindObject<UTexture2D>("Texture2D EngineResources.WhiteSquareTexture");
    UFont *mainFont = UObject::FindObject<UFont>("Font Hud_Items.NameForeground");
    UFont *consoleFont = UObject::FindObject<UFont>("Font EngineFonts.SmallFont");
}

FLinearColor Utils::linCol(const FColor &col)
{
    FLinearColor lcol;
    lcol.R = ((float)col.R / 255);
    lcol.G = ((float)col.G / 255);
    lcol.B = ((float)col.B / 255);
    lcol.A = ((float)col.A / 255);
    return lcol;
}

FColor Utils::rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
    FColor col;
    col.R = r;
    col.G = g;
    col.B = b;
    col.A = alpha;
    return col;
}

FColor Utils::rgb(unsigned char r, unsigned char g, unsigned char b)
{
    return rgba(r, g, b, 255);
}

int Utils::rgb2int(const FColor &col)
{
    return (col.R << 16) | (col.G << 8) | col.B;
}

FColor Utils::lerpColor(const FColor &a, const FColor &b, const float &alpha)
{
    return Utils::engine->LerpColor(a, b, alpha);
}

// Converts UE3's FString to std::string
std::string Utils::f2std(FString &fstr)
{
    if (fstr.Count == 0 || fstr.Data == NULL)
        return "";
    wchar_t *wch = fstr.Data;
    std::wstring wstr(wch);
    return (std::string(wstr.begin(), wstr.end()));
}

// Removes whitespace and lowercases the string
std::string Utils::cleanString(const std::string &str)
{
    std::string out = str;
    out.erase(std::remove(out.begin(), out.end(), ' '), out.end());
    out.erase(std::remove(out.begin(), out.end(), '\t'), out.end());
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return (out);
}

// Removes whitespace from both ends of a string
std::string Utils::trim(const std::string &str)
{
    size_t begin = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (begin == std::string::npos || end == std::string::npos)
        return ("");
    return (str.substr(begin, end - begin + 1));
};

// Converts float seconds to minutes and seconds format
std::string Utils::fTime2string(float time)
{
    int minutes = (int)time / 60;
    float seconds = (int)time % 60 + time - (int)time;

    std::string sMinutes;
    if (minutes == 1)
        sMinutes = std::to_string(minutes) + " minute ";
    else if (minutes > 1)
        sMinutes = std::to_string(minutes) + " minutes ";
    else
        sMinutes = "";

    char sSeconds[15];
    sprintf(sSeconds, "%.3f seconds", seconds);
    
    return (sMinutes + sSeconds);
}

// Converts float seconds to a stopwatch format
std::string Utils::fTime2stopwatch(float time)
{
    int minutes = (int)time / 60;
    int seconds = (int)time % 60;
    int milliseconds = (int)((time - (int)time) * 1000);

    char buff[11];

    sprintf(buff, "%02d:%02d.%d", minutes, seconds, milliseconds);

    return buff;
}

// Returns the config directory path
std::string Utils::getConfigDir()
{
    wchar_t* localDocuments = 0;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &localDocuments);

    if (FAILED(hr)) {
        return "C:\\";
    }

    std::wstring wstr = localDocuments;

    CoTaskMemFree(static_cast<void*>(localDocuments));

    return std::string(wstr.begin(), wstr.end()) + "\\My Games\\Tribes Ascend\\TribesGame\\config\\";
}

bool Utils::fileExists(const std::string &path, const std::string &mode)
{
    if (FILE *file = fopen(path.c_str(), mode.c_str()))
    {
        fclose(file);
        return true;
    }
    return false;
}

bool Utils::dirExists(const std::string &path)
{
    DWORD ftyp = GetFileAttributesA(path.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false; //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true; // this is a directory!

    return false; // this is not a directory!
}

// Regex search in a map of type <string, int> where the string are regexes
// location and print_on_fail are only used for error messages
int Utils::searchMapId(const std::map<std::string, int> map, const std::string &str, const std::string &location, bool print_on_fail)
{
    std::string clean = Utils::cleanString(str);
    for (auto const &it : map)
    {
        
        //Utils::console("A: %s", it.first.c_str());
        
        if (std::regex_match(clean, std::regex(it.first)))
            return (it.second);
    }
    if (!print_on_fail)
        return (0);
    if (!location.size())
        console("WARNING: searched item '%s' could not be identified", str.c_str());
    else
        console("WARNING: searched item '%s' could not be identified as %s", str.c_str(), location.c_str());
    return (0);
}

// Perk encoding

int Utils::perks_Encode(int perkA, int perkB) {
    return (perkA << 16) | perkB;
}

int Utils::perks_DecodeA(int encoded) {
    return encoded >> 16;
}

int Utils::perks_DecodeB(int encoded) {
    return encoded & 0x0000FFFF;
}


void Utils::notify(const std::string &title, const std::string &str)
{
    if (!tr_pc)
        return;
    std::wstring wtitle(title.begin(), title.end());
    std::wstring wstr(str.begin(), str.end());
    wchar_t* wchtitle = (wchar_t *)wtitle.c_str();
    wchar_t* wchstr = (wchar_t *)wstr.c_str();
    tr_pc->ShowNotification(wchstr, wchtitle);
}

// Notify the user (like friend online/offline)
// TODO: use char instead of wchar_t for the title
void Utils::notify(wchar_t *title, const char *format, ...)
{
    if (!tr_pc)
        return;
    va_list args;
    va_start(args, format);
    char buff[256];
    vsprintf(buff, format, args);
    va_end(args);
    std::string str(buff);
    std::wstring wstr = std::wstring(str.begin(), str.end());
    wchar_t* wch = (wchar_t *)wstr.c_str();
    tr_pc->ShowNotification(wch, title);
}

// Print a message in the user's console
// TODO: specify error level (message, log, warning, error, etc)
// TODO: customizable color
void Utils::console(const char *format, ...)
{
    if (!tr_gvc)
        return;
    va_list args;
    va_start(args, format);
    char buff[256];
    vsprintf(buff, format, args);
    va_end(args);
    std::string str(buff);
    printConsole(str, rgb(255, 255, 255));
    Utils::notify(L"TAMods", "Error: see console for details");
}

void Utils::printConsole(const std::string &str)
{
    Utils::printConsole(str, rgb(255, 255, 255));
}

void Utils::printConsole(const std::string &str, const FColor &col)
{
    std::wstring wstr = std::wstring(str.begin(), str.end());
    Utils::printConsole(wstr, col);
}

inline void Utils::printConsole(const std::wstring& wstr, const FColor& col)
{
    wchar_t* wch = (wchar_t*)wstr.c_str();
    Utils::printConsole(wch, col);
}

inline void Utils::printConsole(wchar_t* wch, const FColor& col)
{
    if (!tr_gvc)
        return;
    tr_gvc->ChatConsole->OutputTextLine(wch, col);
}

void Utils::openConsole(const std::string &text)
{
    if (tr_gvc && tr_gvc->ChatConsole)
    {
        UTrChatConsole* con = tr_gvc->ChatConsole;

        if (!con->EqualEqual_NameName(con->GetStateName(), FName("Open"))) {
            con->GotoState(FName("Open"), NULL, NULL, NULL);
        }
            
        con->SetInputText((wchar_t *)std::wstring(text.begin(), text.end()).c_str());
        con->SetCursorPos(text.length());
        con->UpdateCompleteIndices();
    }
}

void Utils::drawTextMain(const std::string &str, const FColor &col, float x, float y, const unsigned char &align, const int &shadowSize, const float &scale, const unsigned &size, const unsigned char &fontNum)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    std::string text = str;
    cryptor.fromId(text);

    UCanvas &canvas = *tr_hud->Canvas;
    float xl, yl;

    std::wstring wstr = std::wstring(text.begin(), text.end());
    wchar_t* wch = (wchar_t *)wstr.c_str();

    switch (fontNum)
    {
    case 1: canvas.Font = mainFont; break;
    case 2: canvas.Font = consoleFont; break;
    case 3: canvas.Font = ut_hud->GetFontSizeIndex(size); break;
    case 4: canvas.Font = UObject::FindObject<UFont>("Font EngineFonts.TinyFont"); break;
    default: canvas.Font = mainFont;
    }

    canvas.StrLen(wch, &xl, &yl);

    xl *= scale;
    yl *= scale;

    // 0=left 1=center 2=right
    if (align == 1)
        x -= xl / 2;
    else if (align == 2)
        x -= xl;

    y -= yl / 2;

    if (fontNum > 1 && shadowSize != 0)
    {
        canvas.DrawColor = { 0, 0, 0, 255 };
        canvas.SetPos(x + shadowSize, y + shadowSize, 0.0f);
        canvas.DrawTextW(wch, true, scale, scale, &tr_hud->m_nNameFontRenderInfo);
    }
    canvas.DrawColor = col;
    canvas.SetPos(x, y, 0.0f);
    canvas.DrawTextW(wch, true, scale, scale, &tr_hud->m_nNameFontRenderInfo);
}

void Utils::drawTextMain(const std::string& str, const FColor& col, float x, float y, const unsigned char& align, const int& shadowSize, const float& scale, const unsigned& size, const char* fontName)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    std::string text = str;
    cryptor.fromId(text);

    UCanvas& canvas = *tr_hud->Canvas;
    float xl, yl;

    std::wstring wstr = std::wstring(text.begin(), text.end());
    wchar_t* wch = (wchar_t*)wstr.c_str();

    // Use the provided fontName
    canvas.Font = UObject::FindObject<UFont>(fontName);

    canvas.StrLen(wch, &xl, &yl);

    xl *= scale;
    yl *= scale;

    // 0=left 1=center 2=right
    if (align == 1)
        x -= xl / 2;
    else if (align == 2)
        x -= xl;

    y -= yl / 2;

    if (shadowSize != 0)
    {
        canvas.DrawColor = { 0, 0, 0, 255 };
        canvas.SetPos(x + shadowSize, y + shadowSize, 0.0f);
        canvas.DrawTextW(wch, true, scale, scale, &tr_hud->m_nNameFontRenderInfo);
    }
    canvas.DrawColor = col;
    canvas.SetPos(x, y, 0.0f);
    canvas.DrawTextW(wch, true, scale, scale, &tr_hud->m_nNameFontRenderInfo);
}

void Utils::drawCustomText(const std::string& str, const FColor& col, float x, float y, const unsigned char& align, const int& shadowSize, const float& scale, const char* fontName)
{
    drawTextMain(str, col, x, y, align, shadowSize, scale, 0, fontName);
}

void Utils::drawText(const std::string &str, const FColor &col, float x, float y, const unsigned char &align, const float &scale)
{
    drawTextMain(str, col, x, y, align, 0, scale, 0, 1);
}

void Utils::drawSmallText(const std::string &str, const FColor &col, float x, float y, const unsigned char &align, const int &shadowSize, const float &scale)
{
    drawTextMain(str, col, x, y, align, shadowSize, scale, 0, 2);
}

void Utils::drawUTText(const std::string &str, const FColor &col, float x, float y, const unsigned char &align, const int &shadowSize, const unsigned &size)
{
    drawTextMain(str, col, x, y, align, shadowSize, 1.0f, size, 3);
}

void Utils::drawUTTextScaled(const std::string &str, const FColor &col, float x, float y, const unsigned char &align, const int &shadowSize, const unsigned &size, const float &scale)
{
    drawTextMain(str, col, x, y, align, shadowSize, scale, size, 3);
}

FVector2D Utils::getTextSize(const std::string &str, const float &scale)
{
    if (!(tr_hud && tr_hud->Canvas))
        return{ 0.0f, 0.0f };

    std::string text = str;
    cryptor.fromId(text);

    UCanvas &canvas = *tr_hud->Canvas;
    float xl, yl;

    std::wstring wstr = std::wstring(text.begin(), text.end());
    wchar_t* wch = (wchar_t *)wstr.c_str();

    canvas.Font = mainFont;
    canvas.StrLen(wch, &xl, &yl);
    return{ xl * scale, yl * scale };
}

FVector2D Utils::getSmallTextSize(const std::string &str, const float &scale)
{
    if (!(tr_hud && tr_hud->Canvas))
        return{ 0.0f, 0.0f };

    std::string text = str;
    cryptor.fromId(text);
    
    UCanvas &canvas = *tr_hud->Canvas;
    float xl, yl;

    std::wstring wstr = std::wstring(text.begin(), text.end());
    wchar_t* wch = (wchar_t *)wstr.c_str();

    canvas.Font = consoleFont;
    canvas.StrLen(wch, &xl, &yl);
    return{ xl * scale, yl * scale };
}

FVector2D Utils::getUTTextSize(const std::string &str, const int &size)
{
    if (!(tr_hud && tr_hud->Canvas))
        return{ 0.0f, 0.0f };

    std::string text = str;
    cryptor.fromId(text);

    UCanvas &canvas = *tr_hud->Canvas;
    float xl, yl;

    std::wstring wstr = std::wstring(text.begin(), text.end());
    wchar_t* wch = (wchar_t *)wstr.c_str();

    canvas.Font = ut_hud->GetFontSizeIndex(size);
    canvas.StrLen(wch, &xl, &yl);
    return{ xl, yl };
}

FVector2D Utils::getUTTextSizeScaled(const std::string &str, const int &size, const float &scale)
{
    FVector2D unscaledRes = getUTTextSize(str, size);
    return{unscaledRes.X * scale, unscaledRes.Y * scale};
}

void Utils::drawRect(const float &x1, const float &y1, const float &x2, const float &y2, const FColor &col)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    UCanvas &canvas = *tr_hud->Canvas;
    canvas.SetDrawColorStruct(col);
    canvas.SetPos(x1, y1, 0.0f);
    canvas.DrawRect(x2 - x1, y2 - y1, whiteTexture);
}

void Utils::drawBox(const float &x1, const float &y1, const float &x2, const float &y2, const FColor &col)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    UCanvas &canvas = *tr_hud->Canvas;
    canvas.SetDrawColorStruct(col);
    canvas.SetPos(x1, y1, 0.0f);
    canvas.DrawBox(x2 - x1, y2 - y1);
}

void Utils::drawProgressBar(float x1, float y1, float x2, float y2, const FColor &col, const unsigned char &dir, const float &alpha)
{
    float width = (x2 - x1) * alpha;
    float height = (y2 - y1) * alpha;

    // Direction 0-3 are up/right/down/left
    if (dir == 0)
        y1 = y2 - height;
    else if (dir == 1)
        x2 = x1 + width;
    else if (dir == 2)
        y2 = y1 + height;
    else
        x1 = x2 - width;

    drawRect(x1, y1, x2, y2, col);
}

void Utils::draw2dLine(const float &x1, const float &y1, const float &x2, const float &y2, const FColor &col)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    tr_hud->Canvas->Draw2DLine(x1, y1, x2, y2, col);
}

void Utils::drawRectTextured(const float& x1, const float& y1, const float& x2, const float& y2, const FColor& col, const char* texName)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    UTexture2D* texture = UObject::FindObject<UTexture2D>(texName);

    if (!texture)
        texture = whiteTexture;

    UCanvas& canvas = *tr_hud->Canvas;
    canvas.SetDrawColorStruct(col);
    canvas.SetPos(x1, y1, 0.0f);
    canvas.DrawRect(x2 - x1, y2 - y1, texture);
}

void Utils::drawLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& perc, const float& width, const FColor& col)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    FVector start(x1, y1, 0.0f);

    // Compute the line direction (end - start)
    float directionX = x2 - x1;
    float directionY = y2 - y1;

    // Scale the direction by the percentage to get the line segment
    float lineSegmentX = directionX * perc;
    float lineSegmentY = directionY * perc;

    // Compute the end position
    FVector end(x1 + lineSegmentX, y1 + lineSegmentY, 0.0f);

    tr_hud->Canvas->DrawTextureLine(start, end, 1.0f, width, col, whiteTexture, 0.0f, 0.0f, 1.0f, 1.0f);
}

void Utils::drawLineTextured(const float& x1, const float& y1, const float& x2, const float& y2, const FVector4& uvMapping, const float& width, const FColor& col, const char* texName)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    UTexture2D* texture = UObject::FindObject<UTexture2D>(texName);

    if (!texture)
        texture = whiteTexture;

    FVector start(x1, y1, 0.0f);

    // Compute the line direction (end - start)
    float directionX = x2 - x1;
    float directionY = y2 - y1;

    float lineSegmentX = directionX;
    float lineSegmentY = directionY;

    // Compute the end position
    FVector end(x1 + lineSegmentX, y1 + lineSegmentY, 0.0f);

    tr_hud->Canvas->DrawTextureLine(start, end, 1.0f, width, col, texture, uvMapping.X, uvMapping.Y, uvMapping.Z, uvMapping.W);
}


void Utils::drawSector(float x, float y, float radius, float startAngle, float endAngle, int segements, const char* texName) {
    const float PI = 3.14159265f;

    if (!(tr_hud && tr_hud->Canvas))
        return;

    UTexture2D* texture = UObject::FindObject<UTexture2D>(texName);

    if (!texture)
        return;

    int numSegments = segements;
    float angleStep = (endAngle - startAngle) / numSegments;

    TArray<FCanvasUVTri> triangles;

    for (int i = 0; i < numSegments; ++i) {
        float angle = startAngle + (i * angleStep);
        float nextAngle = startAngle + ((i + 1) * angleStep);
        float posX = x + radius * std::cos(angle * PI / 180.0);
        float posY = y + radius * std::sin(angle * PI / 180.0);
        float nextPosX = x + radius * std::cos(nextAngle * PI / 180.0);
        float nextPosY = y + radius * std::sin(nextAngle * PI / 180.0);

        FCanvasUVTri triangle;

        triangle.V0_Pos = FVector2D{ x, y };
        triangle.V1_Pos = FVector2D{ posX, posY };
        triangle.V2_Pos = FVector2D{ nextPosX, nextPosY };

        // Hardcode UVs
        triangle.V0_UV = FVector2D{ 0.0f, 0.0f };
        triangle.V1_UV = FVector2D{ 1.0f, 0.0f };
        triangle.V2_UV = FVector2D{ 0.5f, 1.0f };

        triangles.Add(triangle);
    }

    tr_hud->Canvas->DrawTris(texture, triangles);
}


void Utils::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const char* texName)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    UTexture2D* texture = UObject::FindObject<UTexture2D>(texName);


    if (!texture)
        texture = whiteTexture;

    FCanvasUVTri triangle;

    // Assign positions
    triangle.V0_Pos = FVector2D{ x1, y1 };
    triangle.V1_Pos = FVector2D{ x2, y2 };
    triangle.V2_Pos = FVector2D{ x3, y3 };

    // Hardcode UVs
    triangle.V0_UV = FVector2D{ 0.0f, 0.0f };
    triangle.V1_UV = FVector2D{ 1.0f, 0.0f };
    triangle.V2_UV = FVector2D{ 0.5f, 1.0f };

    TArray<FCanvasUVTri> triangles;
    triangles.Add(triangle);

    tr_hud->Canvas->DrawTris(texture, triangles);
}

void Utils::drawCircle(float centerX, float centerY, float radius, const char* texName)
{
    if (!(tr_hud && tr_hud->Canvas))
        return;

    UTexture2D* texture = UObject::FindObject<UTexture2D>(texName);

    if (!texture)
        texture = whiteTexture;

    const float PI = 3.14159;
    const int numSides = 30;  
    const float angleStep = 2.0f * PI / numSides;

    TArray<FCanvasUVTri> triangles;

    for (int i = 0; i < numSides; ++i)
    {
        FCanvasUVTri triangle;

        float curAngle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;
        float curX = centerX + radius * cosf(curAngle);
        float curY = centerY + radius * sinf(curAngle);
        float nextX = centerX + radius * cosf(nextAngle);
        float nextY = centerY + radius * sinf(nextAngle);

        triangle.V0_Pos = FVector2D{ centerX, centerY };
        triangle.V1_Pos = FVector2D{ curX, curY };
        triangle.V2_Pos = FVector2D{ nextX, nextY };
        triangle.V0_UV = FVector2D{ 0.5f, 0.5f };
        triangle.V1_UV = FVector2D{ 0.5f + 0.5f * cosf(curAngle), 0.5f + 0.5f * sinf(curAngle) };
        triangle.V2_UV = FVector2D{ 0.5f + 0.5f * cosf(nextAngle), 0.5f + 0.5f * sinf(nextAngle) };

        triangles.Add(triangle);
    }
    tr_hud->Canvas->DrawTris(texture, triangles);
}

ATrDevice* Utils::getDeviceByEquipPointHelper(unsigned const char &n)
{
    ATrPawn *TrP = Utils::getPlayerPawn();
    if (TrP && TrP->IsAliveAndWell() && TrP->InvManager)
        return ((ATrInventoryManager *)TrP->InvManager)->GetDeviceByEquipPoint(n);

    return NULL;
}

ATrDevice* Utils::getDeviceByWeaponIDHelper(int weapon_id) {
    ATrPawn *TrP = Utils::getPlayerPawn();
    if (TrP && TrP->IsAliveAndWell() && TrP->InvManager)
        return ((ATrInventoryManager *)TrP->InvManager)->GetDeviceByWeaponId(weapon_id);

    return NULL;
}

ATrDevice* Utils::getCurrentDeviceHelper()
{
    ATrPawn *TrP = Utils::getPlayerPawn();
    if (TrP)
        return (ATrDevice *)TrP->Weapon;

    return NULL;
}

ATrPawn* Utils::getPlayerPawn()
{
    if (Utils::tr_pc && Utils::tr_pc->Pawn)
    {
        ATrPawn *TrP = (ATrPawn *)Utils::tr_pc->Pawn;

        if (TrP->IsA(ATrPlayerPawn::StaticClass()))
        {
            return TrP;
        }
        else if (TrP->Weapon && ((ATrVehicleWeapon *)TrP->Weapon)->MyVehicle)
        {
            if (((ATrVehicleWeapon *)TrP->Weapon)->MyVehicle->Driver)
            {
                return (ATrPawn *)((ATrVehicleWeapon *)TrP->Weapon)->MyVehicle->Driver;
            }
        }
    }
    return NULL;
}

void Utils::FindObjects(const std::string &needle, CallbackType callback)
{
    while (!UObject::GObjObjects())
        Sleep(100);

    while (!FName::Names())
        Sleep(100);

    std::regex r(needle, std::regex_constants::icase);

    for (int i = 0; i < UObject::GObjObjects()->Count; ++i)
    {
        UObject* Object = UObject::GObjObjects()->Data[i];

        if (Object && std::regex_search(Object->GetFullName(), r))
        {
            // if the callback function returns true, we stop searching
            if (callback(Object))
                return;
        }
    }
}