#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <GarrysMod/FactoryLoader.hpp>
#include <GarrysMod/Lua/Interface.h>
#include <Platform.hpp>
#include <color.h>
#include <tier0/dbg.h>

#if ARCHITECTURE_IS_X86_64
#include <logging.h>
#endif

void RecolorMsg(int &RED, int &GREEN, int &BLUE) {
  if ((RED == 156 && GREEN == 241 && BLUE == 255) || // Msg
      (RED == 136 && GREEN == 221 && BLUE == 221)    // MsgN
  ) {
    RED = 255;
    GREEN = 181;
    BLUE = 80;
  } else if (RED == 136 && GREEN == 221 && BLUE == 255) { // error
    RED = 255;
    GREEN = 101;
    BLUE = 56;
  }
}

#if ARCHITECTURE_IS_X86_64
class TruetermListener : public ILoggingListener {
public:
  TruetermListener(bool bQuietPrintf = false, bool bQuietDebugger = false) {}

  void Log(const LoggingContext_t *pContext, const char *msg) override {
    int RED = pContext->m_Color.r();
    int GREEN = pContext->m_Color.g();
    int BLUE = pContext->m_Color.b();

    const LoggingSeverity_t Type = pContext->m_Severity;

    bool printcol = RED > 0 || GREEN > 0 || BLUE > 0;
    bool white = RED == 255 && GREEN == 255 && BLUE == 255;

    if (Type == LS_WARNING && white) {
      RED = 255;
      GREEN = 100;
      BLUE = 50;
    } else if (Type == LS_MESSAGE && white) {
      RED = 200;
      GREEN = 235;
      BLUE = 255;
    } else if ((Type == LS_ERROR || Type == LS_ASSERT) && white) {
      RED = 255;
      GREEN = 90;
      BLUE = 90;
    }

    RecolorMsg(RED, GREEN, BLUE);

    if (!printcol) {
      if (Type != LS_MESSAGE) {
        RED = 255;
        BLUE = 255;
      } else {
        printf("%s", msg);
        return;
      }
    }

    char buf[20] = "";
    snprintf(buf, sizeof(buf), "\x1b[38;2;%03d;%03d;%03dm", RED, GREEN, BLUE);

    printf("%s", buf);
    printf("%s", msg);
    printf("\x1b[0m");
  }
};

ILoggingListener *listener = new TruetermListener();
#else
SpewOutputFunc_t spewFunction = nullptr;
SpewRetval_t TruetermSpew(SpewType_t Type, const char *msg) {
  SpewRetval_t ret;

  if (!msg || *msg == '\0')
    return SPEW_CONTINUE;

  const Color *col = GetSpewOutputColor();

  int RED = 0;
  int GREEN = 0;
  int BLUE = 0;
  int ALPHA = 0;

  col->GetColor(RED, GREEN, BLUE, ALPHA);

  bool printcol = RED > 0 || GREEN > 0 || BLUE > 0;
  bool white = RED == 255 && GREEN == 255 && BLUE == 255;

  if (Type == SPEW_WARNING && white) {
    RED = 255;
    GREEN = 100;
    BLUE = 50;
  } else if (Type == SPEW_LOG && white) {
    RED = 200;
    GREEN = 235;
    BLUE = 255;
  } else if ((Type == SPEW_ERROR || Type == SPEW_ASSERT) && white) {
    RED = 255;
    GREEN = 90;
    BLUE = 90;
  }

  RecolorMsg(RED, GREEN, BLUE);

  if (!printcol) {
    if (Type != SPEW_MESSAGE) {
      RED = 255;
      BLUE = 255;
    } else {
      return SPEW_CONTINUE;
    }
  }

  char buf[20] = "";
  snprintf(buf, sizeof(buf), "\x1b[38;2;%03d;%03d;%03dm", r, g, b);

  spewFunction(Type, buf);
  spewFunction(Type, msg);
  spewFunction(Type, "\x1b[0m");

  return SPEW_CONTINUE;
}
#endif

GMOD_MODULE_OPEN() {
#if ARCHITECTURE_IS_X86_64
  LoggingSystem_PushLoggingState(false, false);
  LoggingSystem_RegisterLoggingListener(listener);
#else
  spewFunction = GetSpewOutputFunc();
  SpewOutputFunc(TruetermSpew);

#endif

  return 0;
}

GMOD_MODULE_CLOSE() {
#if ARCHITECTURE_IS_X86_64
  LoggingSystem_UnregisterLoggingListener(listener);
  LoggingSystem_PopLoggingState(false);
  delete listener;
#else
  SpewOutputFunc(spewFunction);
#endif

  return 0;
}
