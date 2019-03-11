##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## build
ProjectName            :=ksamp
ConfigurationName      :=build
WorkspacePath          :=/media/seba/workspace/C
ProjectPath            :=/media/seba/workspace/C/ksamp
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
ObjectsFileList        :="ksamp.txt"
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
Objects0=$(IntermediateDirectory)/ksamp.c$(ObjectSuffix) $(IntermediateDirectory)/info.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/ksamp.c$(ObjectSuffix): ksamp.c $(IntermediateDirectory)/ksamp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/ksamp/ksamp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ksamp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ksamp.c$(DependSuffix): ksamp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ksamp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ksamp.c$(DependSuffix) -MM ksamp.c

$(IntermediateDirectory)/ksamp.c$(PreprocessSuffix): ksamp.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ksamp.c$(PreprocessSuffix) ksamp.c

$(IntermediateDirectory)/info.c$(ObjectSuffix): info.c $(IntermediateDirectory)/info.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/ksamp/info.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/info.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/info.c$(DependSuffix): info.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/info.c$(ObjectSuffix) -MF$(IntermediateDirectory)/info.c$(DependSuffix) -MM info.c

$(IntermediateDirectory)/info.c$(PreprocessSuffix): info.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/info.c$(PreprocessSuffix) info.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./build/


