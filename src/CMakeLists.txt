cmake_minimum_required(VERSION 2.6)

project(MSE)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS regex system thread date_time chrono)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

find_package(wxWidgets REQUIRED COMPONENTS core base media html net)
include(${wxWidgets_USE_FILE})

find_package(HUNSPELL REQUIRED)
include_directories(SYSTEM ${HUNSPELL_INCLUDE_DIRS})

message("Hunspell: " ${HUNSPELL_INCLUDE_DIRS})

if(WIN32)
	add_definitions(-D__WXMSW__)
	set(RESOURCE_FILES resource/msw/mse.rc)
endif(WIN32)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR})

set(CLI_FILES
	cli/cli_main.cpp
	cli/cli_main.hpp
	cli/text_io_handler.cpp
	cli/text_io_handler.hpp)
source_group(cli FILES ${CLI_FILES})

set(DATA_ACTION_FILES
	data/action/generic.hpp
	data/action/keyword.cpp
	data/action/keyword.hpp
	data/action/set.cpp
	data/action/set.hpp
	data/action/symbol.cpp
	data/action/symbol.hpp
	data/action/symbol_part.cpp
	data/action/symbol_part.hpp
	data/action/value.cpp
	data/action/value.hpp)
source_group(data\\action FILES ${DATA_ACTION_FILES})

set(DATA_AUX_FILES
	data/add_cards_script.cpp
	data/add_cards_script.hpp
	data/draw_what.hpp
	data/export_template.cpp
	data/export_template.hpp
	data/filter.hpp
	data/font.cpp
	data/font.hpp
	data/graph_type.hpp
	data/installer.cpp
	data/installer.hpp
	data/keyword.cpp
	data/keyword.hpp
	data/locale.cpp
	data/locale.hpp
	data/pack.cpp
	data/pack.hpp
	data/statistics.cpp
	data/statistics.hpp
	data/symbol_font.cpp
	data/symbol_font.hpp
	data/word_list.cpp
	data/word_list.hpp)
source_group(data\\aux FILES ${DATA_AUX_FILES})

set(DATA_BASE_FILES
	data/card.cpp
	data/card.hpp
	data/field.cpp
	data/field.hpp
	data/game.cpp
	data/game.hpp
	data/set.cpp
	data/set.hpp
	data/settings.cpp
	data/settings.hpp
	data/stylesheet.cpp
	data/stylesheet.hpp
	data/symbol.cpp
	data/symbol.hpp)
source_group(data\\base FILES ${DATA_BASE_FILES})

set(DATA_FIELD_FILES
	data/field/boolean.cpp
	data/field/boolean.hpp
	data/field/choice.cpp
	data/field/choice.hpp
	data/field/color.cpp
	data/field/color.hpp
	data/field/image.cpp
	data/field/image.hpp
	data/field/information.cpp
	data/field/information.hpp
	data/field/multiple_choice.cpp
	data/field/multiple_choice.hpp
	data/field/package_choice.cpp
	data/field/package_choice.hpp
	data/field/symbol.cpp
	data/field/symbol.hpp
	data/field/text.cpp
	data/field/text.hpp)
source_group(data\\filed FILES ${DATA_FIELD_FILES})

set(DATA_FORMAT_FILES
	data/format/apprentice.cpp
	data/format/clipboard.cpp
	data/format/clipboard.hpp
	data/format/formats.cpp
	data/format/formats.hpp
	data/format/html.cpp
	data/format/image.cpp
	data/format/image_to_symbol.cpp
	data/format/image_to_symbol.hpp
	data/format/mse1.cpp
	data/format/mse2.cpp
	data/format/mtg_editor.cpp
	data/format/mws.cpp)
source_group(data\\format FILES ${DATA_FORMAT_FILES})

set(GFX_FILES
	gfx/bezier.cpp
	gfx/bezier.hpp
	gfx/blend_image.cpp
	gfx/color.cpp
	gfx/color.hpp
	gfx/combine_image.cpp
	gfx/generated_image.cpp
	gfx/generated_image.hpp
	gfx/gfx.hpp
	gfx/image_effects.cpp
	gfx/mask_image.cpp
	gfx/polynomial.cpp
	gfx/polynomial.hpp
	gfx/resample_image.cpp
	gfx/resample_text.cpp
	gfx/rotate_image.cpp)
source_group(gfx FILES ${GFX_FILES})

set(GUI_CONTROL_FILES
	gui/control/card_editor.cpp
	gui/control/card_editor.hpp
	gui/control/card_list.cpp
	gui/control/card_list.hpp
	gui/control/card_list_column_select.cpp
	gui/control/card_list_column_select.hpp
	gui/control/card_viewer.cpp
	gui/control/card_viewer.hpp
	gui/control/filter_ctrl.cpp
	gui/control/filter_ctrl.hpp
	gui/control/filtered_card_list.cpp
	gui/control/filtered_card_list.hpp
	gui/control/gallery_list.cpp
	gui/control/gallery_list.hpp
	gui/control/graph.cpp
	gui/control/graph.hpp
	gui/control/image_card_list.cpp
	gui/control/image_card_list.hpp
	gui/control/item_list.cpp
	gui/control/item_list.hpp
	gui/control/keyword_list.cpp
	gui/control/keyword_list.hpp
	gui/control/native_look_editor.cpp
	gui/control/native_look_editor.hpp
	gui/control/package_list.cpp
	gui/control/package_list.hpp
	gui/control/select_card_list.cpp
	gui/control/select_card_list.hpp
	gui/control/text_ctrl.cpp
	gui/control/text_ctrl.hpp
	gui/control/tree_list.cpp
	gui/control/tree_list.hpp)
source_group(gui\\control FILES ${GUI_CONTROL_FILES})

set(GUI_SET_FILES
	gui/set/cards_panel.cpp
	gui/set/cards_panel.hpp
	gui/set/console_panel.cpp
	gui/set/console_panel.hpp
	gui/set/keywords_panel.cpp
	gui/set/keywords_panel.hpp
	gui/set/panel.cpp
	gui/set/panel.hpp
	gui/set/random_pack_panel.cpp
	gui/set/random_pack_panel.hpp
	gui/set/set_info_panel.cpp
	gui/set/set_info_panel.hpp
	gui/set/stats_panel.cpp
	gui/set/stats_panel.hpp
	gui/set/style_panel.cpp
	gui/set/style_panel.hpp
	gui/set/window.cpp
	gui/set/window.hpp)
source_group(gui\\set FILES ${GUI_SET_FILES})

set(GUI_SYMBOL_FILES
	gui/symbol/basic_shape_editor.cpp
	gui/symbol/basic_shape_editor.hpp
	gui/symbol/control.cpp
	gui/symbol/control.hpp
	gui/symbol/editor.cpp
	gui/symbol/editor.hpp
	gui/symbol/part_list.cpp
	gui/symbol/part_list.hpp
	gui/symbol/point_editor.cpp
	gui/symbol/point_editor.hpp
	gui/symbol/select_editor.cpp
	gui/symbol/select_editor.hpp
	gui/symbol/selection.cpp
	gui/symbol/selection.hpp
	gui/symbol/symmetry_editor.cpp
	gui/symbol/symmetry_editor.hpp
	gui/symbol/window.cpp
	gui/symbol/window.hpp)
source_group(gui\\symbol FILES ${GUI_SYMBOL_FILES})

set(GUI_VALUE_FILES
	gui/value/choice.cpp
	gui/value/choice.hpp
	gui/value/color.cpp
	gui/value/color.hpp
	gui/value/editor.cpp
	gui/value/editor.hpp
	gui/value/image.cpp
	gui/value/image.hpp
	gui/value/information.cpp
	gui/value/information.hpp
	gui/value/multiple_choice.cpp
	gui/value/multiple_choice.hpp
	gui/value/package_choice.cpp
	gui/value/package_choice.hpp
	gui/value/symbol.cpp
	gui/value/symbol.hpp
	gui/value/text.cpp
	gui/value/text.hpp)
source_group(gui\\value FILES ${GUI_VALUE_FILES})

set(GUI_FILES
	gui/about_window.cpp
	gui/about_window.hpp
	gui/auto_replace_window.cpp
	gui/auto_replace_window.hpp
	gui/card_select_window.cpp
	gui/card_select_window.hpp
	gui/drop_down_list.cpp
	gui/drop_down_list.hpp
	gui/html_export_window.cpp
	gui/html_export_window.hpp
	gui/icon_menu.cpp
	gui/icon_menu.hpp
	gui/image_slice_window.cpp
	gui/image_slice_window.hpp
	gui/images_export_window.cpp
	gui/images_export_window.hpp
	gui/new_window.cpp
	gui/new_window.hpp
	gui/package_update_list.cpp
	gui/package_update_list.hpp
	gui/packages_window.cpp
	gui/packages_window.hpp
	gui/preferences_window.cpp
	gui/preferences_window.hpp
	gui/print_window.cpp
	gui/print_window.hpp
	gui/profiler_window.cpp
	gui/thumbnail_thread.cpp
	gui/thumbnail_thread.hpp
	gui/update_checker.cpp
	gui/update_checker.hpp
	gui/util.cpp
	gui/util.hpp
	gui/welcome_window.cpp
	gui/welcome_window.hpp)
source_group(gui FILES ${GUI_FILES})

set(RENDER_CARD_FILES
	render/card/viewer.cpp
	render/card/viewer.hpp)
source_group(render\\card FILES ${RENDER_CARD_FILES})

set(RENDER_SYMBOL_FILES
	render/symbol/filter.cpp
	render/symbol/filter.hpp
	render/symbol/viewer.cpp
	render/symbol/viewer.hpp)
source_group(render\\symbol FILES ${RENDER_SYMBOL_FILES})

set(RENDER_TEXT_FILES
	render/text/compound.cpp
	render/text/element.cpp
	render/text/element.hpp
	render/text/font.cpp
	render/text/symbol.cpp
	render/text/viewer.cpp
	render/text/viewer.hpp)
source_group(render\\text FILES ${RENDER_TEXT_FILES})

set(RENDER_VALUE_FILES
	render/value/choice.cpp
	render/value/choice.hpp
	render/value/color.cpp
	render/value/color.hpp
	render/value/image.cpp
	render/value/image.hpp
	render/value/information.cpp
	render/value/information.hpp
	render/value/multiple_choice.cpp
	render/value/multiple_choice.hpp
	render/value/package_choice.cpp
	render/value/package_choice.hpp
	render/value/symbol.cpp
	render/value/symbol.hpp
	render/value/text.cpp
	render/value/text.hpp
	render/value/viewer.cpp
	render/value/viewer.hpp)
source_group(render\\value FILES ${RENDER_VALUE_FILES})

set(SCRIPT_FUNCTIONS_FILES
	script/functions/basic.cpp
	script/functions/construction.cpp
	script/functions/editor.cpp
	script/functions/english.cpp
	script/functions/export.cpp
	script/functions/functions.hpp
	script/functions/image.cpp
	script/functions/regex.cpp
	script/functions/spelling.cpp
	script/functions/util.hpp)
source_group(script\\functions FILES ${SCRIPT_FUNCTIONS_FILES})

set(SCRIPT_FILES
	script/context.cpp
	script/context.hpp
	script/dependency.cpp
	script/dependency.hpp
	script/image.cpp
	script/image.hpp
	script/parser.cpp
	script/parser.hpp
	script/profiler.cpp
	script/profiler.hpp
	script/script.cpp
	script/script.hpp
	script/script_manager.cpp
	script/script_manager.hpp
	script/scriptable.cpp
	script/scriptable.hpp
	script/to_value.hpp
	script/value.cpp
	script/value.hpp)
source_group(script FILES ${SCRIPT_FILES})

set(UTIL_IO_FILES
	util/io/get_member.cpp
	util/io/get_member.hpp
	util/io/package.cpp
	util/io/package.hpp
	util/io/package_manager.cpp
	util/io/package_manager.hpp
	util/io/reader.cpp
	util/io/reader.hpp
	util/io/writer.cpp
	util/io/writer.hpp)
source_group(util\\io FILES ${UTIL_IO_FILES})

set(UTIL_VCS_FILES
	util/vcs/subversion.cpp
	util/vcs/subversion.hpp)
source_group(util\\vcs FILES ${UTIL_VCS_FILES})

set(UTIL_FILES
	util/action_stack.cpp
	util/action_stack.hpp
	util/age.cpp
	util/age.hpp
	util/alignment.cpp
	util/alignment.hpp
	util/angle.hpp
	util/atomic.hpp
	util/defaultable.hpp
	util/delayed_index_maps.hpp
	util/dynamic_arg.hpp
	util/error.cpp
	util/error.hpp
	util/file_utils.cpp
	util/file_utils.hpp
	util/find_replace.hpp
	util/for_each.hpp
	util/index_map.hpp
	util/locale.hpp
	util/order_cache.hpp
	util/platform.hpp
	util/prec.hpp
	util/real_point.hpp
	util/reflect.hpp
	util/regex.cpp
	util/regex.hpp
	util/rotation.cpp
	util/rotation.hpp
	util/smart_ptr.hpp
	util/spec_sort.cpp
	util/spec_sort.hpp
	util/spell_checker.cpp
	util/spell_checker.hpp
	util/string.cpp
	util/string.hpp
	util/tagged_string.cpp
	util/tagged_string.hpp
	util/vcs.cpp
	util/vcs.hpp
	util/vector2d.hpp
	util/version.cpp
	util/version.hpp
	util/window_id.hpp)
source_group(util FILES ${UTIL_FILES})

set(FILES
	code_template.cpp
	code_template.hpp
	main.cpp)

add_executable(mse
	${CLI_FILES}
	${DATA_ACTION_FILES}
	${DATA_AUX_FILES}
	${DATA_BASE_FILES}
	${DATA_FIELD_FILES}
	${DATA_FORMAT_FILES}
	${GFX_FILES}
	${GUI_CONTROL_FILES}
	${GUI_SET_FILES}
	${GUI_SYMBOL_FILES}
	${GUI_VALUE_FILES}
	${GUI_FILES}
	${RENDER_CARD_FILES}
	${RENDER_SYMBOL_FILES}
	${RENDER_TEXT_FILES}
	${RENDER_VALUE_FILES}
	${SCRIPT_FUNCTIONS_FILES}
	${SCRIPT_FILES}
	${UTIL_IO_FILES}
	${UTIL_VCS_FILES}
	${UTIL_FILES}
	${FILES}
	${RESOURCE_FILES})
	
if(WIN32)
	set_property(TARGET mse PROPERTY WIN32_EXECUTABLE ON)
	
endif(WIN32)

target_link_libraries(mse ${Boost_LIBRARIES})
target_link_libraries(mse ${wxWidgets_LIBRARIES})
target_link_libraries(mse ${HUNSPELL_LIBRARIES})

message("${Boost_LIBRARIES} ${wxWidgets_LIBRARIES} ${HUNSPELL_LIBRARIES}")