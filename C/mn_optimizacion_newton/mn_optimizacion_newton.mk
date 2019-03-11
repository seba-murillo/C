##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=mn_optimizacion_newton
ConfigurationName      :=Debug
WorkspacePath          :=/media/seba/workspace/C
ProjectPath            :=/media/seba/workspace/C/mn_optimizacion_newton
IntermediateDirectory  :=./build
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Seba
Date                   :=02/09/19
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
ObjectsFileList        :="mn_optimizacion_newton.txt"
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
Objects0=$(IntermediateDirectory)/optimizacion_newton.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/optimizacion_newton.c$(ObjectSuffix): optimizacion_newton.c $(IntermediateDirectory)/optimizacion_newton.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/seba/workspace/C/mn_optimizacion_newton/optimizacion_newton.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/optimizacion_newton.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/optimizacion_newton.c$(DependSuffix): optimizacion_newton.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/optimizacion_newton.c$(ObjectSuffix) -MF$(IntermediateDirectory)/optimizacion_newton.c$(DependSuffix) -MM optimizacion_newton.c

$(IntermediateDirectory)/optimizacion_newton.c$(PreprocessSuffix): optimizacion_newton.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/optimizacion_newton.c$(PreprocessSuffix) optimizacion_newton.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./build/


