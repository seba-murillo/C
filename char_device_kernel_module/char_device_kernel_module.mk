##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## build
ProjectName            :=char_device_kernel_module
ConfigurationName      :=build
WorkspacePath          :=/media/seba/workspace/C
ProjectPath            :=/media/seba/workspace/C/char_device_kernel_module
IntermediateDirectory  :=./build
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Seba
Date                   :=01/17/19
CodeLitePath           :=/home/seba/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="char_device_kernel_module.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/char_device.c$(ObjectSuffix) $(IntermediateDirectory)/char_device_test.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./build || $(MakeDirCommand) ./build


$(IntermediateDirectory)/.d:
	@test -d ./build || $(MakeDirCommand) ./build

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/char_device.c$(ObjectSuffix): char_device.c $(IntermediateDirectory)/char_device.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/char_device_kernel_module/char_device.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/char_device.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/char_device.c$(DependSuffix): char_device.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/char_device.c$(ObjectSuffix) -MF$(IntermediateDirectory)/char_device.c$(DependSuffix) -MM char_device.c

$(IntermediateDirectory)/char_device.c$(PreprocessSuffix): char_device.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/char_device.c$(PreprocessSuffix) char_device.c

$(IntermediateDirectory)/char_device_test.c$(ObjectSuffix): char_device_test.c $(IntermediateDirectory)/char_device_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/char_device_kernel_module/char_device_test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/char_device_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/char_device_test.c$(DependSuffix): char_device_test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/char_device_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/char_device_test.c$(DependSuffix) -MM char_device_test.c

$(IntermediateDirectory)/char_device_test.c$(PreprocessSuffix): char_device_test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/char_device_test.c$(PreprocessSuffix) char_device_test.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./build/


