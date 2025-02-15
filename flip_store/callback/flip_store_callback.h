#ifndef FLIP_STORE_CALLBACK_H
#define FLIP_STORE_CALLBACK_H
#include <flip_store.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <apps/flip_store_apps.h>
#include <firmwares/flip_store_firmwares.h>
#include <flip_storage/flip_store_storage.h>

#define MAX_LINE_LENGTH 30

extern bool flip_store_app_does_exist;
extern uint32_t selected_firmware_index;

// Function to draw the description on the canvas with word wrapping
void draw_description(Canvas *canvas, const char *user_message, int x, int y);

void flip_store_view_draw_callback_app_list(Canvas *canvas, void *model);

bool flip_store_input_callback(InputEvent *event, void *context);

void flip_store_text_updated_ssid(void *context);

void flip_store_text_updated_pass(void *context);

uint32_t callback_to_submenu(void *context);

uint32_t callback_to_submenu_options(void *context);

uint32_t callback_to_firmware_list(void *context);

uint32_t callback_to_app_list(void *context);

void settings_item_selected(void *context, uint32_t index);

void dialog_delete_callback(DialogExResult result, void *context);
void dialog_firmware_callback(DialogExResult result, void *context);

void popup_callback(void *context);

uint32_t callback_exit_app(void *context);
void callback_submenu_choices(void *context, uint32_t index);

// Add edits by Derek Jamison
typedef enum DataState DataState;
enum DataState
{
    DataStateInitial,
    DataStateRequested,
    DataStateReceived,
    DataStateParsed,
    DataStateParseError,
    DataStateError,
};

typedef enum FlipStoreCustomEvent FlipStoreCustomEvent;
enum FlipStoreCustomEvent
{
    FlipStoreCustomEventProcess,
};

typedef struct DataLoaderModel DataLoaderModel;
typedef bool (*DataLoaderFetch)(DataLoaderModel *model);
typedef char *(*DataLoaderParser)(DataLoaderModel *model);
struct DataLoaderModel
{
    char *title;
    char *data_text;
    DataState data_state;
    DataLoaderFetch fetcher;
    DataLoaderParser parser;
    void *parser_context;
    size_t request_index;
    size_t request_count;
    ViewNavigationCallback back_callback;
    FuriTimer *timer;
};
void flip_store_generic_switch_to_view(FlipStoreApp *app, char *title, DataLoaderFetch fetcher, DataLoaderParser parser, size_t request_count, ViewNavigationCallback back, uint32_t view_id);

void flip_store_loader_draw_callback(Canvas *canvas, void *model);

void flip_store_loader_init(View *view);

void flip_store_loader_free_model(View *view);

bool flip_store_custom_event_callback(void *context, uint32_t index);

#endif // FLIP_STORE_CALLBACK_H
