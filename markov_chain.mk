##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=markov_chain
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/mitch/Documents/sevcon_test
ProjectPath            :=C:/Users/mitch/Documents/sevcon_test/markov_chain
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=mitch
Date                   :=17/11/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
ObjectsFileList        :="markov_chain.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
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
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/mitchstring.c$(ObjectSuffix) $(IntermediateDirectory)/bigrams.c$(ObjectSuffix) $(IntermediateDirectory)/markov.c$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/mitch/Documents/sevcon_test/markov_chain/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix)main.c

$(IntermediateDirectory)/mitchstring.c$(ObjectSuffix): mitchstring.c $(IntermediateDirectory)/mitchstring.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/mitch/Documents/sevcon_test/markov_chain/mitchstring.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mitchstring.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mitchstring.c$(DependSuffix): mitchstring.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mitchstring.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mitchstring.c$(DependSuffix) -MM mitchstring.c

$(IntermediateDirectory)/mitchstring.c$(PreprocessSuffix): mitchstring.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mitchstring.c$(PreprocessSuffix)mitchstring.c

$(IntermediateDirectory)/bigrams.c$(ObjectSuffix): bigrams.c $(IntermediateDirectory)/bigrams.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/mitch/Documents/sevcon_test/markov_chain/bigrams.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bigrams.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bigrams.c$(DependSuffix): bigrams.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bigrams.c$(ObjectSuffix) -MF$(IntermediateDirectory)/bigrams.c$(DependSuffix) -MM bigrams.c

$(IntermediateDirectory)/bigrams.c$(PreprocessSuffix): bigrams.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bigrams.c$(PreprocessSuffix)bigrams.c

$(IntermediateDirectory)/markov.c$(ObjectSuffix): markov.c $(IntermediateDirectory)/markov.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/mitch/Documents/sevcon_test/markov_chain/markov.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/markov.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/markov.c$(DependSuffix): markov.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/markov.c$(ObjectSuffix) -MF$(IntermediateDirectory)/markov.c$(DependSuffix) -MM markov.c

$(IntermediateDirectory)/markov.c$(PreprocessSuffix): markov.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/markov.c$(PreprocessSuffix)markov.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


