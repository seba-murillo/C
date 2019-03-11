##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## build
ProjectName            :=baash
ConfigurationName      :=build
WorkspacePath          :=/media/seba/workspace/C
ProjectPath            :=/media/seba/workspace/C/baash
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
ObjectsFileList        :="baash.txt"
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
Objects0=$(IntermediateDirectory)/baash.c$(ObjectSuffix) $(IntermediateDirectory)/sebastr.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/baash.c$(ObjectSuffix): baash.c $(IntermediateDirectory)/baash.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/baash/baash.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/baash.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/baash.c$(DependSuffix): baash.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/baash.c$(ObjectSuffix) -MF$(IntermediateDirectory)/baash.c$(DependSuffix) -MM baash.c

$(IntermediateDirectory)/baash.c$(PreprocessSuffix): baash.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/baash.c$(PreprocessSuffix) baash.c

$(IntermediateDirectory)/sebastr.c$(ObjectSuffix): sebastr.c $(IntermediateDirectory)/sebastr.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/baash/sebastr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sebastr.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sebastr.c$(DependSuffix): sebastr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sebastr.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sebastr.c$(DependSuffix) -MM sebastr.c

$(IntermediateDirectory)/sebastr.c$(PreprocessSuffix): sebastr.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sebastr.c$(PreprocessSuffix) sebastr.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./build/


