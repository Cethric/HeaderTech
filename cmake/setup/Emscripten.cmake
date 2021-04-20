include_guard(GLOBAL)

include(emscripten/Functions)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build/bin)

set(CMAKE_UNITY_BUILD ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS 11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_SHARED_LIBRARY_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "--ignore-dynamic-linking")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "--ignore-dynamic-linking")
set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG "--ignore-dynamic-linking ")
set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG_SEP "")
set(CMAKE_INCLUDE_FLAG_C "-I")
set(CMAKE_LIBRARY_PATH_FLAG "-L")
set(CMAKE_LIBRARY_PATH_TERMINATOR "")
set(CMAKE_LINK_LIBRARY_FLAG "-l")

set(CMAKE_LINK_LIBRARY_PREFIX "")
set(CMAKE_LINK_LIBRARY_SUFFIX ".js")
set(CMAKE_STATIC_LIBRARY_PREFIX "lib")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".wasm")
set(CMAKE_EXECUTABLE_SUFFIX ".mjs")

set(CMAKE_FIND_LIBRARY_PREFIXES "library" "lib")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".wasm" ".a" ".js" ".mjs")

set(CMAKE_AUTOGEN_ORIGIN_DEPENDS ON)
set(CMAKE_AUTOMOC_COMPILER_PREDEFINES ON)
if (NOT DEFINED CMAKE_AUTOMOC_PATH_PREFIX)
    set(CMAKE_AUTOMOC_PATH_PREFIX OFF)
endif ()
set(CMAKE_AUTOMOC_MACRO_NAMES "Q_OBJECT" "Q_GADGET" "Q_NAMESPACE" "Q_NAMESPACE_EXPORT")

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(SOURCE_MAP_BASE http://localhost:8080/cmake-build-debug-wasm-win/build/)

set(COMMON_FLAGS "-g -g3 -g4 -flto --memory-init-file 1 --profiling --minify 0 --default-obj-ext .obj ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")
set(COMMON_LINK_FLAGS "${COMMON_FLAGS} --source-map-base ${SOURCE_MAP_BASE} --pre-js ${EMSCRIPTEN_ROOT_PATH}/src/emscripten-source-map.min.js --use-preload-plugins --profiling-funcs --emit-symbol-map")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COMMON_LINK_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${COMMON_LINK_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${COMMON_LINK_FLAGS}")


# See https://github.com/emscripten-core/emscripten/blob/main/src/settings.js

em_setting(ASSERTIONS 1 LINK)
em_setting(RUNTIME_LOGGING 0 LINK)
em_setting(STACK_OVERFLOW_CHECK 0 LINK)
em_setting(VERBOSE 0 COMPILE_AND_LINK) # >-- ?
em_setting(INVOKE_RUN 0 LINK)
em_setting(EXIT_RUNTIME 0 LINK)
em_setting(TOTAL_STACK 5242880 LINK)
em_setting(MALLOC dlmalloc LINK)
em_setting(ABORTING_MALLOC 1 LINK)
em_setting(INITIAL_MEMORY 16777216 LINK)
em_setting(MAXIMUM_MEMORY 2147483648 LINK)
em_setting(ALLOW_MEMORY_GROWTH 0 LINK)
#em_setting(MEMORY_GROWTH_GEOMETRIC_STEP 1mb LINK)
em_setting(MEMORY_GROWTH_GEOMETRIC_CAP 100663296 LINK)
#em_setting(MEMORY_GROWTH_LINEAR_STEP -1 LINK)
em_setting(MEMORY64 0 COMPILE_AND_LINK)
em_setting(INITIAL_TABLE -1 LINK)
em_setting(ALLOW_TABLE_GROWTH 0 LINK)
em_setting(GLOBAL_BASE -1 LINK)
em_setting(USE_CLOSURE_COMPILER 1 LINK)
em_setting(CLOSURE_WARNINGS quiet LINK)
em_setting(IGNORE_CLOSURE_COMPILER_ERRORS 0 LINK)
em_setting(DECLARE_ASM_MODULE_EXPORTS 1 LINK)
em_setting(INLINING_LIMIT 0 COMPILE)
em_setting(SUPPORT_BIG_ENDIAN 0 LINK)
em_setting(SAFE_HEAP 0 LINK)
em_setting(SAFE_HEAP_LOG 0 LINK)
em_setting(EMULATE_FUNCTION_POINTER_CASTS 0 LINK)
em_setting(EXCEPTION_DEBUG 0 LINK)
em_setting(DEMANGLE_SUPPORT 1 LINK)
em_setting(LIBRARY_DEBUG 0 LINK)
em_setting(SYSCALL_DEBUG 0 LINK)
em_setting(SOCKET_DEBUG 0 LINK)
em_setting(DYLINK_DEBUG 0 LINK)
em_setting(SOCKET_WEBRTC 0 LINK)
em_setting(WEBSOCKET_URL ws:// LINK)
em_setting(PROXY_POSIX_SOCKETS 0 LINK)
em_setting(WEBSOCKET_SUBPROTOCOL binary LINK)
em_setting(OPENAL_DEBUG 0 LINK)
em_setting(WEBSOCKET_DEBUG 0 LINK)
em_setting(GL_ASSERTIONS 0 LINK)
em_setting(TRACE_WEBGL_CALLS 0 LINK)
em_setting(GL_DEBUG 0 LINK)
em_setting(GL_TESTING 0 LINK)
em_setting(GL_MAX_TEMP_BUFFER_SIZE 2097152 LINK)
em_setting(GL_UNSAFE_OPTS 1 LINK)
em_setting(FULL_ES2 0 LINK)
em_setting(GL_EMULATE_GLES_VERSION_STRING_FORMAT 1 LINK)
em_setting(GL_EXTENSIONS_IN_PREFIXED_FORMAT 1 LINK)
em_setting(GL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS 1 LINK)
em_setting(GL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS 1 LINK)
em_setting(GL_TRACK_ERRORS 1 LINK)
em_setting(GL_SUPPORT_EXPLICIT_SWAP_CONTROL 0 LINK)
em_setting(GL_POOL_TEMP_BUFFERS 1 LINK)
em_setting(WORKAROUND_OLD_WEBGL_UNIFORM_UPLOAD_IGNORED_OFFSET_BUG 0 LINK)
#em_setting(GL_EXPLICIT_UNIFORM_LOCATION 0 LINK)
em_setting(USE_WEBGL2 0 LINK)
em_setting(MIN_WEBGL_VERSION 1 LINK)
em_setting(MAX_WEBGL_VERSION 1 LINK)
em_setting(WEBGL2_BACKWARDS_COMPATIBILITY_EMULATION 0 LINK)
em_setting(FULL_ES3 0 LINK)
em_setting(LEGACY_GL_EMULATION 0 LINK)
em_setting(GL_FFP_ONLY 0 LINK)
em_setting(GL_PREINITIALIZED_CONTEXT 0 LINK)
em_setting(USE_WEBGPU 0 LINK)
em_setting(STB_IMAGE 0 LINK)
em_setting(GL_DISABLE_HALF_FLOAT_EXTENSION_IF_BROKEN 0 LINK)
em_setting(GL_WORKAROUND_SAFARI_GETCONTEXT_BUG 1 LINK)
em_setting(JS_MATH 0 LINK)
em_setting(POLYFILL_OLD_MATH_FUNCTIONS 0 LINK)
em_setting(LEGACY_VM_SUPPORT 0 LINK)
em_setting(ENVIRONMENT "'web'" LINK)
em_setting(LZ4 1 LINK)
#em_setting(DISABLE_EXCEPTION_CATCHING 1 COMPILE_AND_LINK)
em_setting(EXCEPTION_CATCHING_ALLOWED "[]" COMPILE_AND_LINK)
em_setting(NODEJS_CATCH_EXIT 1 LINK)
em_setting(NODEJS_CATCH_REJECTION 1 LINK)
em_setting(ASYNCIFY 0 LINK)
em_setting(ASYNCIFY_IMPORTS "[]" LINK)
em_setting(ASYNCIFY_IGNORE_INDIRECT 0 LINK)
em_setting(ASYNCIFY_STACK_SIZE 4096 LINK)
em_setting(ASYNCIFY_REMOVE "[]" LINK)
em_setting(ASYNCIFY_ADD "[]" LINK)
em_setting(ASYNCIFY_ONLY "[]" LINK)
em_setting(ASYNCIFY_ADVISE 0 LINK)
em_setting(ASYNCIFY_LAZY_LOAD_CODE 0 LINK)
em_setting(ASYNCIFY_DEBUG 0 LINK)
em_setting(EXPORTED_RUNTIME_METHODS "[]" LINK)
em_setting(EXTRA_EXPORTED_RUNTIME_METHODS "[]" LINK)
set(
        INCOMING_MODULE_JS_API
        ENVIRONMENT
        GL_MAX_TEXTURE_IMAGE_UNITS
        SDL_canPlayWithWebAudio
        SDL_numSimultaneouslyQueuedBuffers
        INITIAL_MEMORY
        wasmMemory
        arguments
        buffer
        canvas
        doNotCaptureKeyboard
        dynamicLibraries
        elementPointerLock
        extraStackTrace
        forcedAspectRatio
        instantiateWasm
        keyboardListeningElement
        freePreloadedMediaOnUse
        locateFile
        logReadFiles
        mainScriptUrlOrBlob
        mem
        monitorRunDependencies
        noExitRuntime
        noInitialRun
        onAbort
        onCustomMessage
        onExit
        onFree
        onFullScreen
        onMalloc
        onRealloc
        onRuntimeInitialized
        postMainLoop
        postRun
        preInit
        preMainLoop
        preRun
        preinitializedWebGLContext
        memoryInitializerRequest
        preloadPlugins
        print
        printErr
        quit
        setStatus
        statusMessage
        stderr
        stdin
        stdout
        thisProgram
        wasm
        wasmBinary
        websocket
)
em_setting(INCOMING_MODULE_JS_API ${INCOMING_MODULE_JS_API} LINK)
em_setting(CASE_INSENSITIVE_FS 0 LINK)
em_setting(FILESYSTEM 1 LINK)
em_setting(FORCE_FILESYSTEM 0 LINK)
em_setting(NODERAWFS 0 LINK)
em_setting(NODE_CODE_CACHING 0 LINK)
em_setting(EXPORTED_FUNCTIONS "[]" LINK)
em_setting(EXPORT_ALL 0 LINK)
em_setting(RETAIN_COMPILER_SETTINGS 1 LINK)
em_setting(DEFAULT_LIBRARY_FUNCS_TO_INCLUDE "[]" LINK)
em_setting(LIBRARY_DEPS_TO_AUTOEXPORT memcpy LINK)
em_setting(INCLUDE_FULL_LIBRARY 0 LINK)
em_setting(SHELL_FILE 0 LINK)
em_setting(RELOCATABLE 0 COMPILE_AND_LINK)
em_setting(MAIN_MODULE 0 COMPILE_AND_LINK)
em_setting(SIDE_MODULE 0 COMPILE_AND_LINK)
em_setting(RUNTIME_LINKED_LIBS "[]" LINK)
em_setting(BUILD_AS_WORKER 0 LINK)
em_setting(PROXY_TO_WORKER 0 LINK)
em_setting(PROXY_TO_WORKER_FILENAME '' LINK)
em_setting(PROXY_TO_PTHREAD 0 LINK)
em_setting(LINKABLE 0 LINK)
em_setting(STRICT 1 COMPILE_AND_LINK)
em_setting(IGNORE_MISSING_MAIN 0 LINK)
em_setting(AUTO_ARCHIVE_INDEXES 0 LINK)
em_setting(STRICT_JS 1 LINK)
em_setting(WARN_ON_UNDEFINED_SYMBOLS 1 LINK)
em_setting(ERROR_ON_UNDEFINED_SYMBOLS 1 LINK)
em_setting(SMALL_XHR_CHUNKS 0 LINK)
em_setting(HEADLESS 0 LINK)
em_setting(DETERMINISTIC 0 LINK)
em_setting(MODULARIZE 1 LINK)
em_setting(EXPORT_ES6 1 LINK)
em_setting(USE_ES6_IMPORT_META 1 LINK)
em_setting(BENCHMARK 0 LINK)
em_setting(EXPORT_NAME VoxelTech LINK)
em_setting(DYNAMIC_EXECUTION 1 LINK)
em_setting(BOOTSTRAPPING_STRUCT_INFO 0 LINK)
em_setting(EMSCRIPTEN_TRACING 0 COMPILE_AND_LINK)
em_setting(USE_GLFW 2 LINK)
em_setting(WASM 1 LINK)
em_setting(STANDALONE_WASM 0 LINK)
em_setting(BINARYEN_IGNORE_IMPLICIT_TRAPS 0 LINK)
em_setting(BINARYEN_EXTRA_PASSES 0 LINK)
em_setting(WASM_ASYNC_COMPILATION 1 LINK)
em_setting(DYNCALLS 0 LINK)
em_setting(WASM_BIGINT 0 LINK)
em_setting(EMIT_PRODUCERS_SECTION 1 LINK)
em_setting(EMIT_EMSCRIPTEN_METADATA 0 LINK)
em_setting(EMIT_EMSCRIPTEN_LICENSE 1 LINK)
em_setting(LEGALIZE_JS_FFI 1 LINK)
em_setting(USE_SDL 0 LINK)
em_setting(USE_SDL_GFX 0 LINK)
em_setting(USE_SDL_IMAGE 0 LINK)
em_setting(USE_SDL_TTF 0 LINK)
em_setting(USE_SDL_NET 0 LINK)
em_setting(USE_SDL_MIXER 0 LINK)
em_setting(SDL2_IMAGE_FORMATS "[]" LINK)
em_setting(SDL2_MIXER_FORMATS "['ogg']" LINK)
em_setting(USE_ICU 0 LINK)
em_setting(USE_ZLIB 0 LINK)
em_setting(USE_BZIP2 0 LINK)
em_setting(USE_GIFLIB 0 LINK)
em_setting(USE_LIBJPEG 0 LINK)
em_setting(USE_LIBPNG 0 LINK)
em_setting(USE_REGAL 0 LINK)
em_setting(USE_BOOST_HEADERS 0 LINK)
em_setting(USE_BULLET 0 LINK)
em_setting(USE_VORBIS 0 LINK)
em_setting(USE_OGG 0 LINK)
em_setting(USE_MPG123 0 LINK)
em_setting(USE_FREETYPE 0 LINK)
em_setting(USE_HARFBUZZ 0 LINK)
em_setting(USE_COCOS2D 0 LINK)
em_setting(USE_MODPLUG 0 LINK)
em_setting(USE_PTHREADS 0 COMPILE_AND_LINK)
em_setting(IN_TEST_HARNESS 0 LINK)
em_setting(PTHREAD_POOL_SIZE 0 LINK)
em_setting(PTHREAD_POOL_SIZE_STRICT 1 LINK)
em_setting(PTHREAD_POOL_DELAY_LOAD 0 LINK)
em_setting(DEFAULT_PTHREAD_STACK_SIZE 2097152 LINK)
em_setting(PTHREADS_PROFILING 0 LINK)
em_setting(ALLOW_BLOCKING_ON_MAIN_THREAD 1 LINK)
em_setting(PTHREADS_DEBUG 0 LINK)
em_setting(EVAL_CTORS 0 LINK)
em_setting(TEXTDECODER 1 LINK)
em_setting(EMBIND_STD_STRING_IS_UTF8 1 LINK)
em_setting(OFFSCREENCANVAS_SUPPORT 0 LINK)
em_setting(OFFSCREENCANVASES_TO_PTHREAD "#canvas" LINK)
em_setting(OFFSCREEN_FRAMEBUFFER 0 LINK)
em_setting(FETCH_SUPPORT_INDEXEDDB 1 LINK)
em_setting(FETCH_DEBUG 0 LINK)
em_setting(FETCH 0 LINK)
em_setting(ASMFS 0 LINK)
em_setting(SINGLE_FILE 0 LINK)
em_setting(AUTO_JS_LIBRARIES 1 LINK)
em_setting(AUTO_NATIVE_LIBRARIES 1 LINK)
em_setting(MIN_FIREFOX_VERSION 65 LINK)
em_setting(MIN_SAFARI_VERSION 120000 LINK)
em_setting(MIN_IE_VERSION 0x7FFFFFFF LINK)
em_setting(MIN_EDGE_VERSION 44 LINK)
em_setting(MIN_CHROME_VERSION 75 LINK)
em_setting(SUPPORT_ERRNO 1 LINK)
em_setting(MINIMAL_RUNTIME 0 LINK)
em_setting(MINIMAL_RUNTIME_STREAMING_WASM_COMPILATION 0 LINK)
em_setting(MINIMAL_RUNTIME_STREAMING_WASM_INSTANTIATION 0 LINK)
em_setting(USES_DYNAMIC_ALLOC 1 LINK)
em_setting(SUPPORT_LONGJMP 1 LINK)
em_setting(DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR 1 LINK)
em_setting(HTML5_SUPPORT_DEFERRING_USER_SENSITIVE_REQUESTS 1 LINK)
em_setting(MINIFY_HTML 1 LINK)
em_setting(MAYBE_WASM2JS 0 LINK)
em_setting(ASAN_SHADOW_SIZE -1 LINK)
em_setting(DISABLE_EXCEPTION_THROWING 0 LINK)
em_setting(USE_OFFSET_CONVERTER 0 LINK)
em_setting(LLD_REPORT_UNDEFINED 0 LINK)
em_setting(DEFAULT_TO_CXX 1 LINK)
em_setting(PRINTF_LONG_DOUBLE 0 LINK)
em_setting(WASM2C 0 LINK)
em_setting(SEPARATE_DWARF_URL "'${SOURCE_MAP_BASE}'" LINK)
em_setting(ERROR_ON_WASM_CHANGES_AFTER_LINK 0 LINK)
em_setting(ABORT_ON_WASM_EXCEPTIONS 0 LINK)
em_setting(PURE_WASI 0 LINK)
em_setting(IMPORTED_MEMORY 1 LINK)
em_setting(SPLIT_MODULE 0 LINK)
em_setting(REVERSE_DEPS "'auto'" LINK)
em_setting(OFFSCREEN_FRAMEBUFFER_FORBID_VAO_PATH 0 LINK)

