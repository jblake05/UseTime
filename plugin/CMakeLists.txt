cmake_minimum_required(VERSION 3.22)

set(OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out)
set(PLUGIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/plugin/AudioPlugin_artefacts/Debug/VST3/UseTime.vst3/Contents/x86_64-win)

project(UseTime VERSION 0.1.0)

juce_add_plugin(${PROJECT_NAME}    
    IS_SYNTH FALSE
    COMPANY_NAME :gt
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE 
    PLUGIN_CODE AUPL 
    FORMATS Standalone VST3 AU
    PRODUCT_NAME "UseTime"
    COPY_PLUGIN_AFTER_BUILD TRUE
    VST3_COPY_DIR "C:/Program Files/Common Files/VST3/" 
)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        juce::juce_audio_utils
    PUBLIC 
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
    )
endif()

# message("Source file path: ${CMAKE_SOURCE_DIR}/time.txt")
# C:\Users\Jeff\Desktop\Audio Programming\UseTime\time.txt
# C:/Users/Jeff/Desktop/Audio Programming/UseTime/time.txt

add_custom_target(copy_txt_vst ALL
    COMMAND ${CMAKE_COMMAND} -E echo "-----------------------------Copying to VST3 Folder-----------------------------"  # Debugging line
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/time.txt
            "C:/Program Files/Common Files/VST3/UseTime.vst3/Contents/x86_64-win/time.txt"
)

# add_custom_target(copy_txt_build ALL
#     COMMAND ${CMAKE_COMMAND} -E echo "-----------------------------Copying to build Folder-----------------------------"  # Debugging line
#     COMMAND ${CMAKE_COMMAND} -E copy
#             ${CMAKE_SOURCE_DIR}/time.txt
#             ${PLUGIN_DIR}/time.txt
# )

# add_custom_command(
#         TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E echo "Running custom post-build command"  # Debugging line
#         COMMAND ${CMAKE_COMMAND} -E copy
#                 ${CMAKE_SOURCE_DIR}/time.txt
#                 "C:/Program Files/Common Files/VST3/UseTime.vst3/Contents/x86_64-win/time.txt"
# )

# Ensure that the custom command is triggered *after* the plugin target is built
# add_dependencies(copy_txt ${PROJECT_NAME})

# Define a dummy target for the copy step, so dependencies are correct
# add_custom_target(time_txt_copy_dependency ALL)