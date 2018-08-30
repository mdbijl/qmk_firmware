/* Reregistering keys */

static bool reregister_lgui;
static bool reregister_rgui;
static bool reregister_lalt;
static bool reregister_ralt;

void reset_reregistering(void);
bool unregister_if_needed(uint8_t code);
void reregister_if_needed(void);
