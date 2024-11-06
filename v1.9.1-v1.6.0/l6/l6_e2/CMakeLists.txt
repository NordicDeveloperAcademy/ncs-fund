#
# Copyright (c) 2016 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.20.0)

set(PM_STATIC_YML_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/boards/pm_static_${BOARD}.yml
  )

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

# Preinitialization related to Thingy:53 DFU
target_sources_ifdef(CONFIG_BOARD_THINGY53_NRF5340_CPUAPP app PRIVATE
  boards/thingy53.c
)
target_sources_ifdef(CONFIG_BOARD_THINGY53_NRF5340_CPUAPP_NS app PRIVATE
  boards/thingy53.c
)
target_sources(app PRIVATE src/main.c)

