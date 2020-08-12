LOCAL_PATH := $(call get_local_path)
include $(DEFAULT_VARIABLES)

$(call add_pkg_config,libcurl)

LOCAL_TARGET := curling

include $(BUILD_STATIC_LIBRARY)