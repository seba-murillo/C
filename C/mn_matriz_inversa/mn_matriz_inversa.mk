##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## build
ProjectName            :=mn_matriz_inversa
ConfigurationName      :=build
WorkspacePath          :=/media/seba/workspace/C
ProjectPath            :=/media/seba/workspace/C/mn_matriz_inversa
IntermediateDirectory  :=./build
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Seba
Date                   :=02/21/19
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
ObjectsFileList        :="mn_matriz_inversa.txt"
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
Objects0=$(IntermediateDirectory)/mn_matriz_inversa.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/mn_matriz_inversa.c$(ObjectSuffix): mn_matriz_inversa.c $(IntermediateDirectory)/mn_matriz_inversa.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/mn_matriz_inversa/mn_matriz_inversa.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mn_matriz_inversa.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mn_matriz_inversa.c$(DependSuffix): mn_matriz_inversa.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mn_matriz_inversa.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mn_matriz_inversa.c$(DependSuffix) -MM mn_matriz_inversa.c

$(IntermediateDirectory)/mn_matriz_inversa.c$(PreprocessSuffix): mn_matriz_inversa.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mn_matriz_inversa.c$(PreprocessSuffix) mn_matriz_inversa.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./build/


