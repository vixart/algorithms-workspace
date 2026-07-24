# Workspace Makefile (mirror of Taskfile.yml).
#
# Usage:
#   make test  DIR=<name>   # build & run one subproject's unit tests
#   make run   DIR=<name>   # build & run one subproject's demo (main.cpp)
#   make test-all           # build & run every subproject's tests
#   make clean              # remove built binaries
#
# On Windows call it as: mingw32-make <target>

CXX      := g++
# -static* keeps the binaries self-contained (no libstdc++-6.dll / libgcc_s_seh-1.dll
# runtime dependency). Keep in sync with Taskfile.yml's CXXFLAGS.
CXXFLAGS := -std=c++23 -Wall -Wextra -O2 -Icommon -static -static-libgcc -static-libstdc++
DOCMAIN  := common/doctest_main.cpp

ifeq ($(OS),Windows_NT)
  SHELL := cmd.exe
  EXE   := .exe
  # convert forward slashes to backslashes for cmd.exe program invocation
  FIXP   = $(subst /,\,$1)
else
  EXE   :=
  FIXP   = $1
endif

# All subproject folders that contain unit tests (excluding the _template).
SUBPROJECTS := $(filter-out _template,$(sort $(patsubst %/,%,$(dir $(wildcard */*_test.cpp)))))

.PHONY: help test test-all run clean list

.DEFAULT_GOAL := help

help:
	@echo Targets:
	@echo   make test DIR=^<name^>   - build ^& run one subproject's tests
	@echo   make run  DIR=^<name^>   - build ^& run one subproject's demo
	@echo   make test-all           - run every subproject's tests
	@echo   make clean              - remove built binaries
	@echo   make list               - list subprojects

list:
	@echo $(SUBPROJECTS)

test:
	@$(if $(DIR),,$(error DIR is not set. Use: make test DIR=<name>))
	$(CXX) $(CXXFLAGS) $(wildcard $(DIR)/*_test.cpp) $(DOCMAIN) -o $(DIR)/.test_runner$(EXE)
	$(call FIXP,$(DIR)/.test_runner$(EXE))

run:
	@$(if $(DIR),,$(error DIR is not set. Use: make run DIR=<name>))
	$(CXX) $(CXXFLAGS) $(DIR)/main.cpp -o $(DIR)/.demo$(EXE)
	$(call FIXP,$(DIR)/.demo$(EXE))

test-all:
	$(foreach d,$(SUBPROJECTS),$(MAKE) --no-print-directory test DIR=$(d) &&) cd .

clean:
ifeq ($(OS),Windows_NT)
	-@del /S /Q /F .test_runner.exe .demo.exe 2>nul
else
	-@find . \( -name '.test_runner' -o -name '.demo' \) -delete
endif
