#include <list>
#include <vector>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Tools/Includes/Logger.h"
#include "Tools/Includes/obfuscate.h"
#include "Tools/Includes/Utils.h"

#include "Tools/SOCKET/client.h"
#include "Tools/SOCKET/IncludeClient.h"
#include "Widgets/ImportWidgets.h"
#include "Tools/DrawTools/Draw.h"
#include <chrono>
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shreekant_Menu_imageBase64(JNIEnv* env, jobject thiz) {
    return env->NewStringUTF(OBFUSCATE("iVBORw0KGgoAAAANSUhEUgAAALQAAAC0CAMAAAAKE/YAAAABCGlDQ1BJQ0MgUHJvZmlsZQAAeJxjYGA8wQAELAYMDLl5JUVB7k4KEZFRCuwPGBiBEAwSk4sLGHADoKpv1yBqL+viUYcLcKakFicD6Q9ArFIEtBxopAiQLZIOYWuA2EkQtg2IXV5SUAJkB4DYRSFBzkB2CpCtkY7ETkJiJxcUgdT3ANk2uTmlyQh3M/Ck5oUGA2kOIJZhKGYIYnBncAL5H6IkfxEDg8VXBgbmCQixpJkMDNtbGRgkbiHEVBYwMPC3MDBsO48QQ4RJQWJRIliIBYiZ0tIYGD4tZ2DgjWRgEL7AwMAVDQsIHG5TALvNnSEfCNMZchhSgSKeDHkMyQx6QJYRgwGDIYMZAKbWPz9HbOBQAAABgFBMVEVgGuKfIl+dWuRZJiLVIxfkWx/wn6DoX1/gYJ+iIiPynGSdKZzk1t1fIVxkIKNjUyH31aWcXhyWJ+TSK2JoW+yjnZ9pYFyjU6Xt3ynjo+HXZNwrGKWhV2HdnyIuJN/x4V2mlyKhme6jl2IjJR0jJVlqUaIO5fQKoRDQMpUXXRIgWusOn9prkfULzgrMDukRWJogT2QYlqKuzPBwkI1hkmEWqGSXyW1fkR1p1Vaz0KYi0VV00dxa0jGhyiZE0KQIBQcsCDL7+vgVFRItBRAuCktLGG5LFVI2FFAXBSs2FWpOBRAsCm74lwn62AlPGIssFw785gn6pggrKCn6xwhPCTD6twhvBg02NjMWBk73iAcuJRJLDEluCTEvFo7u6OwvFTSNBwsvCI1tJW+QGFJsGmyNJ4xtFVJLJw+OCC1UI5BIRkePFgv66c8YCm2PJXGwFwuuKGz0Vwn+9Q+vBwv3181yJY+uJlLPN1JuFRHwNwppKLH3eAbvWG9SFqzTR2/yZ40aWYLzAAAAgHRSTlP//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////xUHpOoAAD/sSURBVHjazZ2JQ1pLtu7ZbqYNbJAgIApxTB8z9En6nL7dfYf3GEXFgYgIEQeMGjXqcYhj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"));
}

struct {
    bool enableESP = false;
    bool AimSilent = false;
    bool AimSilent360 = false;
    bool autoswitch = false;

    bool downaimkill = false;
    bool resetguest = false;
    bool telekill = false;
    bool Aimkilltpv2 = false;
    bool Aimkillrotate = false;
    bool Aimkillrotatev2 = false;
    bool Aimkillrotatev3 = false;
    bool Aimkilltp = false;
    bool downplayer = false;
    bool highjump = false;
    bool medikitrun = false;
    bool ultraswitch = false;
    bool speedhackjoy = false;
    bool speedrun = false;
    bool cameraup = false;
    bool wallHack = false;
    bool teleportcar = false;
    bool doublegun = false;
    bool upplayerx = false;
    bool telehack = false;
    bool aimbody = false;
    bool TeleBeta = false;
    bool climbup = false;
    float FlyUp = 0.0f;
    int FlySpeed = 0;
    float vehicle_y = 0.0f;
    float vehicle_unY = 0.0f;
} MasterBool;

struct {
    bool enableAimbot = false;
    bool aimbotShoot = false;
    bool aimbotScope = false;
    bool Aimkill = false;
    bool Aimkill360 = false;
    bool teleprt = false;

    bool Aimkillrage = false;
    bool aimbot = false;
    bool SilentAim = false;
    bool aimbotbody = false;
    bool UnlimitedAmmo = false;
    bool norecoil = false;
    float aimbotFOV = 0.0f;
    float aimbotSmoothness = 20.0f;
    float speedValue = 0.0f;
    bool speedHack = false;
} pAimbotPlayer;

struct {
    bool espLine = false;
    bool espBox = false;
    bool espInfo = false;
    bool espHealth = false;
    bool DISC = false;
    bool espDrawFov = false;
    bool espTracker = false;
    bool espLineTracker = false;
    Color espColor = Color::White();
    Color espnameColor = Color::White();
    bool espNickName = false;
    int lineType = 0;
    int boxType = 0;
} pEspPlayer;

struct {
    bool speedHack = false;
    bool undergroundCatapult = false;
    bool catapultDistance = false;
} pMemoryTools;

using namespace std;

std::string LoggedInOwnerID = "";

bool showAnimation = false;
long long animationStartTime = 0;

int frameCount = 0;
float fpsValue = 0.0f;
long long lastFpsTime = 0;

long long getCurrentTimeMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

struct FeatureNotification {
    char name[64];
    bool enabled;
    long long startTime;
    bool active;
} currentNotification;

void showNotification(const char* name, bool enabled) {
    strcpy(currentNotification.name, name);
    currentNotification.enabled = enabled;
    currentNotification.startTime = getCurrentTimeMs();
    currentNotification.active = true;
}

// Called from Java to send owner ID

// Show toast from native
void ShowErrorToast(JNIEnv* env, const char* message) {
    jclass cls = env->FindClass("com/shreekant/Login");
    if (!cls) return;

    jmethodID method = env->GetStaticMethodID(cls, "showToastFromNative", "(Landroid/content/Context;Ljava/lang/String;)V");
    if (!method) return;

    jfieldID contextField = env->GetStaticFieldID(cls, "globalContext", "Landroid/content/Context;");
    jobject context = env->GetStaticObjectField(cls, contextField);
    if (!context) return;

    jstring jMessage = env->NewStringUTF(message);
    env->CallStaticVoidMethod(cls, method, context, jMessage);
    env->DeleteLocalRef(jMessage);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_shreekant_Login_sendOwnerIDToNative(JNIEnv* env, jobject, jstring ownerId) {
    const char *nativeStr = env->GetStringUTFChars(ownerId, 0);
    LoggedInOwnerID = std::string(nativeStr);
    env->ReleaseStringUTFChars(ownerId, nativeStr);

    LOGD("🔒 Owner ID received from Java: %s", LoggedInOwnerID.c_str());

    if (LoggedInOwnerID == "8Z9qRQ2zph") {
    } else {
        LOGD("❌ Blocked features for unknown owner ID: %s", LoggedInOwnerID.c_str());
    }
}



extern "C"
JNIEXPORT void JNICALL
Java_com_shreekant_Menu_Init(JNIEnv *env, jclass thiz) {
    startClient();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shreekant_Menu_Functions(JNIEnv *env, jclass clazz) {
    Widget widget = Widget(env);
    widget.Tab("Functions");
    widget.Tab1("Functions");
    // ---------------- Aim Features ----------------
    widget.Category(OBFUSCATE("Aimbot Features"));
    widget.Switch(OBFUSCATE("Activate All"), 102);
    widget.Switch(OBFUSCATE("Silent Aim"), 103);
    widget.Switch(OBFUSCATE("Drag Headshot"), 1055);
    widget.Switch(OBFUSCATE("Sniper Auto Aim"), 500);
    widget.Switch(OBFUSCATE("Up Player"), 20);
    widget.Switch(OBFUSCATE("Show Fov"), 16);
    widget.SeekBar(OBFUSCATE("Adjust Headshot Rate"), 0, 100, "%", 104);

    // ---------------- ESP Features ----------------
    widget.Category(OBFUSCATE("ESP"));
    widget.Switch(OBFUSCATE("ESP Line"), 1);
    widget.Switch(OBFUSCATE("ESP Box"), 2);
    widget.Switch(OBFUSCATE("ESP Name"), 4);
    widget.Switch(OBFUSCATE("ESP Health"), 9);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_shreekant_Menu_ChangesID(JNIEnv *env, jclass clazz, jint id, jint value) {
    switch (id) {


        case 102: { // ENABLE ALL
            if (LoggedInOwnerID.find("8Z9qRQ2zph") != std::string::npos) {

                pAimbotPlayer.enableAimbot = !pAimbotPlayer.enableAimbot;
                SendFeatuere(101, pAimbotPlayer.enableAimbot);
                MasterBool.enableESP = !MasterBool.enableESP;
                SendFeatuere(3, MasterBool.enableESP);

                MasterBool.ultraswitch = !MasterBool.ultraswitch;
                SendFeatuere(212, MasterBool.ultraswitch);

                if (pAimbotPlayer.enableAimbot) {
                    showAnimation = true;
                    animationStartTime = getCurrentTimeMs();
                } else {
                    showAnimation = false;
                }
                showNotification("Activate All", pAimbotPlayer.enableAimbot);
            } else {
                ShowErrorToast(env, "SHREEKANT PANEL ALWAYS ON TOP ✅.   ");
                LOGD("❌ BLOCKED: Owner ID mismatch! Found: %s", LoggedInOwnerID.c_str());
            }
            break;
        }


        case 103:
            pAimbotPlayer.Aimkill = !pAimbotPlayer.Aimkill;
            SendFeatuere(103, pAimbotPlayer.Aimkill);
            showNotification("Silent Aim", pAimbotPlayer.Aimkill);
            break;
        case 1055:
            pAimbotPlayer.Aimkill360 = !pAimbotPlayer.Aimkill360;
            SendFeatuere(1055, pAimbotPlayer.Aimkill360);
            showNotification("Drag Headshot", pAimbotPlayer.Aimkill360);
            break;
        case 7581:
            pAimbotPlayer.Aimkillrage = !pAimbotPlayer.Aimkillrage;
            SendFeatuere(7581, pAimbotPlayer.Aimkillrage);
            break;
        case 104:
            pAimbotPlayer.aimbotFOV = value;
            SendFOV(104, value);
            break;

        case 105:
            pAimbotPlayer.aimbot = !pAimbotPlayer.aimbot;
            SendFeatuere(105, pAimbotPlayer.aimbot);
            break;

        case 106:
            pAimbotPlayer.norecoil = !pAimbotPlayer.norecoil;
            SendFeatuere(106, pAimbotPlayer.norecoil);
            break;

        case 107:
            pAimbotPlayer.aimbotSmoothness = value;
            SendFOV(107, value);
            break;
        case 1044:
            MasterBool.FlyUp = value;
            SendFOV(1044, value);
            break;
        case 1043:
            MasterBool.FlySpeed = value;
            SendFOV(1043, value);
            break;
        case 108:
            pAimbotPlayer.aimbotbody = !pAimbotPlayer.aimbotbody;
            SendFeatuere(108, pAimbotPlayer.aimbotbody);
            break;

        case 109:
            pAimbotPlayer.speedHack = !pAimbotPlayer.speedHack;
            SendFeatuere(109, pAimbotPlayer.speedHack);
            break;
        case 147:
            pAimbotPlayer.UnlimitedAmmo = !pAimbotPlayer.UnlimitedAmmo;
            SendFeatuere(147, pAimbotPlayer.UnlimitedAmmo);
            break;
        case 110:
            pAimbotPlayer.speedValue = value;
            SendFOV(110, value);
            break;

        case 111:
            pAimbotPlayer.SilentAim = !pAimbotPlayer.SilentAim;
            SendFeatuere(111, pAimbotPlayer.SilentAim);
            break;
        case 550:
            pAimbotPlayer.teleprt = !pAimbotPlayer.teleprt;
            SendFeatuere(550, pAimbotPlayer.teleprt);
            break;

        case 1:
            pEspPlayer.espLine = !pEspPlayer.espLine;
            SendFeatuere(3, pEspPlayer.espLine || pEspPlayer.espBox || pEspPlayer.espNickName || pEspPlayer.espHealth);
            showNotification("ESP Line", pEspPlayer.espLine);
            break;

        case 2:
            pEspPlayer.espBox = !pEspPlayer.espBox;
            SendFeatuere(3, pEspPlayer.espLine || pEspPlayer.espBox || pEspPlayer.espNickName || pEspPlayer.espHealth);
            showNotification("ESP Box", pEspPlayer.espBox);
            break;

        case 3:
            pEspPlayer.espHealth = !pEspPlayer.espHealth;
            SendFeatuere(3, pEspPlayer.espLine || pEspPlayer.espBox || pEspPlayer.espNickName || pEspPlayer.espHealth);
            showNotification("ESP Health", pEspPlayer.espHealth);
            break;
        case 33333:
            pEspPlayer.DISC = !pEspPlayer.DISC;
            break;

        case 4:
            pEspPlayer.espNickName = !pEspPlayer.espNickName;
            SendFeatuere(3, pEspPlayer.espLine || pEspPlayer.espBox || pEspPlayer.espNickName || pEspPlayer.espHealth);
            showNotification("ESP Name", pEspPlayer.espNickName);
            break;

        case 5:
            if (value == 0) {
                pEspPlayer.espColor = Color::White();
            } else if (value == 1) {
                pEspPlayer.espColor = Color::Green();
            } else if (value == 2) {
                pEspPlayer.espColor = Color::Blue();
            } else if (value == 3) {
                pEspPlayer.espColor = Color::Red();
            } else if (value == 4) {
                pEspPlayer.espColor = Color::Black();
            } else if (value == 5) {
                pEspPlayer.espColor = Color::Yellow();
            } else if (value == 6) {
                pEspPlayer.espColor = Color::Cyan();
            } else if (value == 7) {
                pEspPlayer.espColor = Color::Magenta();
            } else if (value == 8) {
                pEspPlayer.espColor = Color::Gray();
            } else if (value == 9) {
                pEspPlayer.espColor = Color::Purple();
            }
            break;

        case 6:
            if (value == 0) {
                pEspPlayer.lineType = value;
            } else if (value == 1) {
                pEspPlayer.lineType = value;
            } else if (value == 2) {
                pEspPlayer.lineType = value;
            }
            break;

        case 7:
            if (value == 0) {
                pEspPlayer.boxType = value;
            } else if (value == 1) {
                pEspPlayer.boxType = value;
            } else if (value == 2) {
                pEspPlayer.boxType = value;
            }
            break;

        case -2:
            pMemoryTools.catapultDistance = !pMemoryTools.catapultDistance;
            SendFeatuere(5, pMemoryTools.catapultDistance);
            break;

        case 16:
            pEspPlayer.espDrawFov = !pEspPlayer.espDrawFov;
            showNotification("Show Fov", pEspPlayer.espDrawFov);
            break;

        case 9:
            pEspPlayer.espHealth = !pEspPlayer.espHealth;
            SendFeatuere(3, pEspPlayer.espLine || pEspPlayer.espBox || pEspPlayer.espNickName || pEspPlayer.espHealth);
            showNotification("ESP Health", pEspPlayer.espHealth);
            break;
        case 14:
            pEspPlayer.espTracker = !pEspPlayer.espTracker;
            break;
        case 144:
            pEspPlayer.espLineTracker = !pEspPlayer.espTracker;
            break;

        case 10:
            MasterBool.ultraswitch = !MasterBool.ultraswitch;
            SendFeatuere(10, MasterBool.ultraswitch);
            break;
        case 11:
            MasterBool.highjump = !MasterBool.highjump;
            SendFeatuere(11, MasterBool.highjump);
            break;
        case 12:
            MasterBool.resetguest = !MasterBool.resetguest;
            SendFeatuere(12, MasterBool.resetguest);
            break;

        case 13:
            MasterBool.medikitrun = !MasterBool.medikitrun;
            SendFeatuere(13, MasterBool.medikitrun);
            break;
        case 1111:
            MasterBool.cameraup = !MasterBool.cameraup;
            SendFeatuere(1111, MasterBool.cameraup);
            break;
        case 15:
            MasterBool.speedhackjoy = !MasterBool.speedhackjoy;
            SendFeatuere(15, MasterBool.speedhackjoy);
            break;
        case 17:
            MasterBool.doublegun = !MasterBool.doublegun;
            SendFeatuere(17, MasterBool.doublegun);
            break;
        case 166:
            MasterBool.wallHack = !MasterBool.wallHack;
            SendFeatuere(166, MasterBool.wallHack);
            break;
        case 19:
            MasterBool.telehack = !MasterBool.telehack;
            SendFeatuere(19, MasterBool.telehack);
            break;
        case 20:
            MasterBool.upplayerx = !MasterBool.upplayerx;
            SendFeatuere(20, MasterBool.upplayerx);
            showNotification("Up Player", MasterBool.upplayerx);
            break;
        case 21:
            MasterBool.aimbody = !MasterBool.aimbody;
            SendFeatuere(21, MasterBool.aimbody);
            break;
        case 22:
            MasterBool.AimSilent = !MasterBool.AimSilent;
            SendFeatuere(22, MasterBool.AimSilent);
            break;
        case 1056:
            MasterBool.AimSilent360 = !MasterBool.AimSilent360;
            SendFeatuere(1056, MasterBool.AimSilent360);
            break;
        case 500:
            MasterBool.Aimkilltp = !MasterBool.Aimkilltp;
            SendFeatuere(500, MasterBool.Aimkilltp);
            showNotification("Sniper Auto Aim", MasterBool.Aimkilltp);
            break;
        case 501:
            MasterBool.Aimkilltpv2 = !MasterBool.Aimkilltpv2;
            SendFeatuere(501, MasterBool.Aimkilltpv2);
            break;
        case 502:
            MasterBool.Aimkillrotate = !MasterBool.Aimkillrotate;
            SendFeatuere(502, MasterBool.Aimkillrotate);
            break;
        case 503:
            MasterBool.Aimkillrotatev2 = !MasterBool.Aimkillrotatev2;
            SendFeatuere(503, MasterBool.Aimkillrotatev2);
            break;
        case 504:
            MasterBool.downaimkill = !MasterBool.downaimkill;
            SendFeatuere(504, MasterBool.downaimkill);
            break;
        case 505:
            MasterBool.autoswitch = !MasterBool.autoswitch;
            SendFeatuere(505, MasterBool.autoswitch);
            break;

        case 506:
            MasterBool.Aimkillrotatev3 = !MasterBool.Aimkillrotatev3;
            SendFeatuere(506, MasterBool.Aimkillrotatev3);
            break;
        case 507:
            MasterBool.speedrun = !MasterBool.speedrun;
            SendFeatuere(507, MasterBool.speedrun);
            break;
        case 508:
            MasterBool.TeleBeta = !MasterBool.TeleBeta;
            SendFeatuere(508, MasterBool.TeleBeta);
            showNotification("Sniper Auto Aim", MasterBool.TeleBeta);
            break;
        case 509:
            MasterBool.climbup = !MasterBool.climbup;
            SendFeatuere(509, MasterBool.climbup);
            break;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shreekant_Menu_OnDrawLoad(JNIEnv *env, jclass clazz, jobject draw_view, jobject canvas) {
    DrawView draw = DrawView(env, draw_view, canvas);

    std::string userLicenseKey = "admin";
    jclass menuClass = env->FindClass("com/shreekant/Menu");
    if (menuClass != nullptr) {
        jfieldID keyField = env->GetStaticFieldID(menuClass, "userLicenseKey", "Ljava/lang/String;");
        if (keyField != nullptr) {
            jstring jKeyStr = (jstring) env->GetStaticObjectField(menuClass, keyField);
            if (jKeyStr != nullptr) {
                const char *keyChars = env->GetStringUTFChars(jKeyStr, nullptr);
                if (keyChars != nullptr) {
                    userLicenseKey = std::string(keyChars);
                    env->ReleaseStringUTFChars(jKeyStr, keyChars);
                }
            }
        }
    }

    if (draw.isValid()) {
        // Automatically start signature key intro animation on initial load after login
        if (animationStartTime == 0) {
            animationStartTime = getCurrentTimeMs();
            showAnimation = true;
        }

        // Real-time FPS Calculation and Drawing in Bottom-Left Corner
        long long currentTime = getCurrentTimeMs();
        frameCount++;
        if (currentTime - lastFpsTime >= 1000) {
            fpsValue = frameCount * 1000.0f / (currentTime - lastFpsTime);
            frameCount = 0;
            lastFpsTime = currentTime;
        }

        char fpsText[32];
        sprintf(fpsText, "FPS- %.0f", fpsValue);
        Vector2 fpsPos(30.0f, (float)draw.getHeight() - 40.0f);
        draw.DrawText(Color(0, 0, 0, 200), fpsText, Vector2(fpsPos.X + 2.0f, fpsPos.Y + 2.0f), 30.0f);
        draw.DrawText(Color(255, 184, 0, 255), fpsText, fpsPos, 30.0f);

        if (pEspPlayer.espDrawFov) {
            // Draw a White circle with thicker line (4.0 thickness) at center of screen.
            // Radius scales dynamically with "Adjust Headshot Rate" (pAimbotPlayer.aimbotFOV: 0-100)
            float radius = 50.0f + (pAimbotPlayer.aimbotFOV * 4.0f);
            // Draw glowing outer layers in White
            draw.DrawCircle(Color(255, 255, 255, 35), 8.0f, Vector2(draw.getWidth() / 2, draw.getHeight() / 2), radius + 2.0f);
            draw.DrawCircle(Color(255, 255, 255, 75), 5.0f, Vector2(draw.getWidth() / 2, draw.getHeight() / 2), radius + 1.0f);
            // Main circle in White
            draw.DrawCircle(Color(255, 255, 255, 255), 4.0f, Vector2(draw.getWidth() / 2, draw.getHeight() / 2), radius);
        }

        // --- Ultra-Smooth Cursive Signature Writing Animation (Exactly 3.0 sec total) ---
        if (showAnimation) {
            long long elapsed = getCurrentTimeMs() - animationStartTime;
            Vector2 centerPos(draw.getWidth() / 2.0f, draw.getHeight() / 2.0f);
            float signatureSize = 210.0f;
            if (draw.getWidth() >= 1920 || draw.getHeight() >= 1920) {
                signatureSize = 240.0f;
            }

            long long writeDuration = 1900; // 1.9s graceful letter-by-letter handwriting sweep + swash
            long long holdDuration = 600;   // 0.6s glowing neon hold with breathing pulse
            long long fadeDuration = 500;   // 0.5s smooth dissolve into game

            if (elapsed < writeDuration) {
                // Phase 1: Real-time cursive handwriting animation (letter-by-letter with glowing fountain pen spark nib)
                draw.DrawBlackScreen(255);
                float linearProgress = (float)elapsed / (float)writeDuration;
                draw.DrawSmoothSignatureWriting(Color(255, 255, 255, 255), userLicenseKey.c_str(), centerPos, signatureSize, linearProgress);
            }
            else if (elapsed < writeDuration + holdDuration) {
                // Phase 2: Complete signature text glowing brightly at center with subtle breathing pulse
                draw.DrawBlackScreen(255);
                long long holdElapsed = elapsed - writeDuration;
                float pulse = 0.5f + 0.5f * sinf((float)holdElapsed / 95.0f);
                int glowAlpha = 230 + (int)(25.0f * pulse);
                draw.DrawSmoothSignatureWriting(Color(255, 255, 255, glowAlpha), userLicenseKey.c_str(), centerPos, signatureSize, 1.0f);
            }
            else if (elapsed < writeDuration + holdDuration + fadeDuration) {
                // Phase 3: Smooth dissolve fade-out into game
                long long fadeElapsed = elapsed - (writeDuration + holdDuration);
                float fadeProgress = (float)fadeElapsed / (float)fadeDuration;
                if (fadeProgress > 1.0f) fadeProgress = 1.0f;

                float smoothFade = fadeProgress * fadeProgress * (3.0f - 2.0f * fadeProgress);
                int screenAlpha = (int)(255 * (1.0f - smoothFade));
                int textAlpha = (int)(255 * (1.0f - smoothFade));

                draw.DrawBlackScreen(screenAlpha);
                draw.DrawSmoothSignatureWriting(Color(255, 255, 255, textAlpha), userLicenseKey.c_str(), centerPos, signatureSize, 1.0f);
            }
            else {
                // Animation finished!
                showAnimation = false;
            }
        }

        // Show Logo overlay at top center when Activate All is ON and animation is not running
        if (pAimbotPlayer.enableAimbot && !showAnimation) {
            draw.DrawLogo(draw.getWidth() / 2.0f, 75.0f, 110.0f, 110.0f, 255.0f);
        }

        if (pAimbotPlayer.enableAimbot) {
            Response response = getData(draw.getWidth(), draw.getHeight());

            if (response.Success) {
            for (int i = 0; i < response.PlayerCount; ++i) {
                PlayerData data = response.Players[i];

                Vector3 HeadLoc = data.headPosition;
                Vector3 PesLoc = data.bottomPlayerPosition;

                if (HeadLoc.Z < -1) continue;
                if (PesLoc.Z < -1) continue;

                float distance = data.distance;
                float health = data.health;
                bool IsCaido = data.isDieing;

                // Limit scale for ESP
                float scale = std::max(0.5f, std::min(1.0f, 500.0f / distance));

                // Calculate player box dimensions
                float boxHeight = abs(HeadLoc.Y - PesLoc.Y) * scale;
                float boxWidth = boxHeight * 0.50f;

                // Adjust position for head alignment
                Rect PlayerRect(HeadLoc.X - (boxWidth / 2), draw.getHeight() - HeadLoc.Y, boxWidth, boxHeight);

                if (pEspPlayer.espLine) {
                    Vector2 lineStart;
                    Vector2 lineEnd;

                    if (pEspPlayer.lineType == 0) {
                        lineStart = Vector2(draw.getWidth() / 2, 130.0f);
                        lineEnd = Vector2(HeadLoc.X, draw.getHeight() - HeadLoc.Y);
                    } else if (pEspPlayer.lineType == 1) {
                        lineStart = Vector2(draw.getWidth() / 2, draw.getHeight() / 2);
                        lineEnd = Vector2(HeadLoc.X, draw.getHeight() - HeadLoc.Y);
                    } else if (pEspPlayer.lineType == 2) {
                        lineStart = Vector2(draw.getWidth() / 2, draw.getHeight());
                        lineEnd = Vector2(PesLoc.X, draw.getHeight() - PesLoc.Y);
                    }

                    if (IsCaido) {
                        draw.DrawLine(Color::Red(), 3.5f, lineStart, lineEnd);
                    } else {
                        draw.DrawLine(pEspPlayer.espColor, 3.5f, lineStart, lineEnd);
                    }
                }

                if (pEspPlayer.espBox) {
                    if (IsCaido) {
                        if (pEspPlayer.boxType == 0) {
                            // Draw red glowing border
                            Rect glowRect(PlayerRect.x - 1, PlayerRect.y - 1, PlayerRect.w + 2, PlayerRect.h + 2);
                            draw.DrawBox(Color(255, 0, 0, 45), 5.5f, glowRect);
                            draw.DrawBox(Color::Red(), 2.5f, PlayerRect);
                        } else if (pEspPlayer.boxType == 1) {
                            draw.DrawBox3D(Color::Red(), 2.5f, PlayerRect, 10);
                        } else if (pEspPlayer.boxType == 2) {
                            draw.DrawCornerBox(Color::Red(), 2.5f, PlayerRect, 4, 4);
                        }
                    } else {
                        if (pEspPlayer.boxType == 0) {
                            // Draw customizable color glowing border
                            Rect glowRect(PlayerRect.x - 1, PlayerRect.y - 1, PlayerRect.w + 2, PlayerRect.h + 2);
                            Color glowColor = pEspPlayer.espColor;
                            glowColor.a = 45;
                            draw.DrawBox(glowColor, 5.5f, glowRect);
                            draw.DrawBox(pEspPlayer.espColor, 2.5f, PlayerRect);
                        } else if (pEspPlayer.boxType == 1) {
                            draw.DrawBox3D(pEspPlayer.espColor, 2.5f, PlayerRect, 10);
                        } else if (pEspPlayer.boxType == 2) {
                            draw.DrawCornerBox(pEspPlayer.espColor, 2.5f, PlayerRect, 4, 4);
                        }
                    }
                }

                // ======= Draw Nickname =======
                if(pEspPlayer.espNickName)
                {
                    if (!IsCaido) {

                        Vector2 namePos(HeadLoc.X, draw.getHeight() - HeadLoc.Y - 20);
                        std::string playerName = data.name;
                        draw.DrawTextWithShadow(pEspPlayer.espColor, playerName.c_str(), namePos, 16, Vector2(2, 2), 0.5f);

                    }
                }
                // ======= Draw Distance =======
                if (pEspPlayer.DISC) {
                    float centerX = draw.getWidth() / 2.0f;
                    float centerY = draw.getHeight() / 2.0f;

                    if (!IsCaido) {
                        Vector2 namePos(PlayerRect.x + (PlayerRect.w / 2), PlayerRect.y - (5.0f * scale));
                        namePos.X -= (strlen(data.name) * 2.5f * scale);
                        float textSize = 12.0f * scale;
                        Vector2 shadowOffset(1.0f, 1.0f);
                        char distanceText[32];
                        sprintf(distanceText, "%dm", static_cast<int>(data.distance));

                        // Calculate centered position for distance text
                        float textWidth = strlen(distanceText) * 6.0f * scale; // Approximate text width
                        Vector2 distancePos(
                                PlayerRect.x + (PlayerRect.w / 2) - (textWidth / 2),
                                PlayerRect.y + PlayerRect.h + (18.0f * scale) // Increased from 12.0f to 18.0f to move it further down
                        );

                        // Draw black border
                        draw.DrawTextWithShadow(Color(0, 0, 0, 255), distanceText, Vector2(distancePos.X - 1, distancePos.Y), textSize, shadowOffset, 2.0f);
                        draw.DrawTextWithShadow(Color(0, 0, 0, 255), distanceText, Vector2(distancePos.X + 1, distancePos.Y), textSize, shadowOffset, 2.0f);
                        draw.DrawTextWithShadow(Color(0, 0, 0, 255), distanceText, Vector2(distancePos.X, distancePos.Y - 1), textSize, shadowOffset, 2.0f);
                        draw.DrawTextWithShadow(Color(0, 0, 0, 255), distanceText, Vector2(distancePos.X, distancePos.Y + 1), textSize, shadowOffset, 2.0f);

                        // Draw main text
                        draw.DrawTextWithShadow(Color(255, 255, 255, 255), distanceText, distancePos, textSize, shadowOffset, 2.0f);
                    }
                }





                // ======= Health Bar =======
                if (pEspPlayer.espHealth && !IsCaido) {
                    Vector2 healthBarPos(PlayerRect.x - 5.0f * scale, PlayerRect.y);
                    float healthBarHeight = boxHeight;
                    draw.DrawVerticalHealthBar(healthBarPos, healthBarHeight, 200.0f, data.health);
                }
            }
        } else {
            // Draw simulated mock players for testing preview when not connected to daemon
            int simulatedCount = 2;
            for (int i = 0; i < simulatedCount; ++i) {
                float headX, headY, bottomX, bottomY, distance, health;
                const char* name;

                if (i == 0) {
                    headX = draw.getWidth() * 0.70f;
                    headY = draw.getHeight() * 0.40f;
                    bottomX = draw.getWidth() * 0.70f;
                    bottomY = draw.getHeight() * 0.65f;
                    distance = 45.0f;
                    health = 200.0f;
                    name = "Training BOT 1";
                } else {
                    headX = draw.getWidth() * 0.30f;
                    headY = draw.getHeight() * 0.30f;
                    bottomX = draw.getWidth() * 0.30f;
                    bottomY = draw.getHeight() * 0.75f;
                    distance = 15.0f;
                    health = 100.0f;
                    name = "Training BOT 2";
                }

                float scale = std::max(0.5f, std::min(1.0f, 500.0f / distance));
                float boxHeight = abs(headY - bottomY) * scale;
                float boxWidth = boxHeight * 0.50f;

                Rect PlayerRect(headX - (boxWidth / 2), headY, boxWidth, boxHeight);

                if (pEspPlayer.espLine) {
                    Vector2 lineStart;
                    Vector2 lineEnd(headX, headY);

                    if (pEspPlayer.lineType == 0) {
                        lineStart = Vector2(draw.getWidth() / 2, 130.0f);
                    } else if (pEspPlayer.lineType == 1) {
                        lineStart = Vector2(draw.getWidth() / 2, draw.getHeight() / 2);
                    } else {
                        lineStart = Vector2(draw.getWidth() / 2, draw.getHeight());
                        lineEnd = Vector2(bottomX, bottomY);
                    }

                    draw.DrawLine(pEspPlayer.espColor, 3.5f, lineStart, lineEnd);
                }

                if (pEspPlayer.espBox) {
                    if (pEspPlayer.boxType == 0) {
                        // Draw customizable color glowing border
                        Rect glowRect(PlayerRect.x - 1, PlayerRect.y - 1, PlayerRect.w + 2, PlayerRect.h + 2);
                        Color glowColor = pEspPlayer.espColor;
                        glowColor.a = 45;
                        draw.DrawBox(glowColor, 5.5f, glowRect);
                        draw.DrawBox(pEspPlayer.espColor, 2.5f, PlayerRect);
                    } else if (pEspPlayer.boxType == 1) {
                        draw.DrawBox3D(pEspPlayer.espColor, 2.5f, PlayerRect, 10);
                    } else if (pEspPlayer.boxType == 2) {
                        draw.DrawCornerBox(pEspPlayer.espColor, 2.5f, PlayerRect, 4, 4);
                    }
                }

                if (pEspPlayer.espNickName) {
                    Vector2 namePos(headX, headY - 20);
                    draw.DrawTextWithShadow(pEspPlayer.espColor, name, namePos, 16, Vector2(2, 2), 0.5f);
                }

                if (pEspPlayer.espHealth) {
                    Vector2 healthBarPos(PlayerRect.x - 5.0f * scale, PlayerRect.y);
                    float healthBarHeight = boxHeight;
                    draw.DrawVerticalHealthBar(healthBarPos, healthBarHeight, 200.0f, health);
                }
            }
        }
    }


        // --- Premium Bottom-Right Notification Toast ---
        if (currentNotification.active) {
            long long elapsed = currentTime - currentNotification.startTime;
            if (elapsed < 2500) {
                int alpha = 255;
                if (elapsed < 300) {
                    alpha = (int)(255 * (elapsed / 300.0f));
                } else if (elapsed > 2200) {
                    alpha = (int)(255 * ((2500 - elapsed) / 300.0f));
                }
                if (alpha < 0) alpha = 0;
                if (alpha > 255) alpha = 255;

                float toastWidth = 360.0f;
                float toastHeight = 85.0f;
                float toastX = (float)draw.getWidth() - toastWidth - 30.0f;
                float toastY = (float)draw.getHeight() - toastHeight - 50.0f;

                if (elapsed < 300) {
                    float progress = elapsed / 300.0f;
                    toastX = (float)draw.getWidth() - (toastWidth + 30.0f) * progress;
                } else if (elapsed > 2200) {
                    float progress = (2500 - elapsed) / 300.0f;
                    toastX = (float)draw.getWidth() - (toastWidth + 30.0f) * progress;
                }

                // 1. Draw card background (semi-transparent dark)
                draw.DrawFilledRectinfo(Color(20, 20, 20, (int)(alpha * 0.92f)), Rect(toastX, toastY, toastWidth, toastHeight));

                // 2. Draw card outline box (Gold VIP theme border)
                Color outlineColor = Color(255, 23, 68, alpha);
                draw.DrawBox(outlineColor, 1.5f, Rect(toastX, toastY, toastWidth, toastHeight));

                // 3. Draw thick left accent stripe
                draw.DrawFilledRectinfo(outlineColor, Rect(toastX, toastY, 6.0f, toastHeight));

                // 4. Draw Bell / Star Emoji on the left
                draw.DrawText(Color(255, 255, 255, alpha), "⚡", Vector2(toastX + 35.0f, toastY + 53.0f), 28.0f);

                // 5. Draw Title: "SHREEKANT PANEL" in bold gold (left-aligned)
                draw.DrawTextLeft(Color(0, 0, 0, (int)(alpha * 0.8f)), "SHREEKANT PANEL", Vector2(toastX + 70.0f + 1.0f, toastY + 28.0f + 1.0f), 12.0f);
                draw.DrawTextLeft(outlineColor, "SHREEKANT PANEL", Vector2(toastX + 70.0f, toastY + 28.0f), 12.0f);

                // 6. Draw Status Message: "[Feature] : ACTIVE" (left-aligned)
                char statusText[96];
                if (currentNotification.enabled) {
                    sprintf(statusText, "%s : ACTIVE 🟢", currentNotification.name);
                } else {
                    sprintf(statusText, "%s : OFF ⚪", currentNotification.name);
                }

                Color textColor = currentNotification.enabled ? Color(0, 230, 118, alpha) : Color(180, 180, 180, alpha);

                draw.DrawTextLeft(Color(0, 0, 0, (int)(alpha * 0.8f)), statusText, Vector2(toastX + 70.0f + 1.0f, toastY + 58.0f + 1.0f), 18.0f);
                draw.DrawTextLeft(textColor, statusText, Vector2(toastX + 70.0f, toastY + 58.0f), 18.0f);
            } else {
                currentNotification.active = false;
            }
        }

        // ESP Line Tracker and Name Tracker removed as per user request

    }
}