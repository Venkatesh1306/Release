#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=libModbusRtu/crcRTU.c libModbusRtu/modbusRtuError.c libModbusRtu/modbusRtuFrame.c libModbusRtu/modbusRtuPacketParse.c libModbusRtu/presetMultipleReg.c libModbusRtu/presetSingleReg.c libModbusRtu/readHoldingReg.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/libModbusRtu/crcRTU.o ${OBJECTDIR}/libModbusRtu/modbusRtuError.o ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o ${OBJECTDIR}/libModbusRtu/presetSingleReg.o ${OBJECTDIR}/libModbusRtu/readHoldingReg.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/libModbusRtu/crcRTU.o.d ${OBJECTDIR}/libModbusRtu/modbusRtuError.o.d ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o.d ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o.d ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o.d ${OBJECTDIR}/libModbusRtu/presetSingleReg.o.d ${OBJECTDIR}/libModbusRtu/readHoldingReg.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/libModbusRtu/crcRTU.o ${OBJECTDIR}/libModbusRtu/modbusRtuError.o ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o ${OBJECTDIR}/libModbusRtu/presetSingleReg.o ${OBJECTDIR}/libModbusRtu/readHoldingReg.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=libModbusRtu/crcRTU.c libModbusRtu/modbusRtuError.c libModbusRtu/modbusRtuFrame.c libModbusRtu/modbusRtuPacketParse.c libModbusRtu/presetMultipleReg.c libModbusRtu/presetSingleReg.c libModbusRtu/readHoldingReg.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24EP128GP202
MP_LINKER_FILE_OPTION=,--script=p24EP128GP202.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/libModbusRtu/crcRTU.o: libModbusRtu/crcRTU.c  .generated_files/flags/default/9096b0f9615ff9266eb8b24e9971a9fbba5aca6f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/crcRTU.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/crcRTU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/crcRTU.c  -o ${OBJECTDIR}/libModbusRtu/crcRTU.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/crcRTU.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/modbusRtuError.o: libModbusRtu/modbusRtuError.c  .generated_files/flags/default/c91ba86d011bba62a196222c9a1ca29bb7adb4e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuError.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuError.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/modbusRtuError.c  -o ${OBJECTDIR}/libModbusRtu/modbusRtuError.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/modbusRtuError.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o: libModbusRtu/modbusRtuFrame.c  .generated_files/flags/default/91a26aa0788b7955ab647601dbb9298a7556df81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/modbusRtuFrame.c  -o ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o: libModbusRtu/modbusRtuPacketParse.c  .generated_files/flags/default/b44da7460160ca2a959f9056b5e86914fb70bcff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/modbusRtuPacketParse.c  -o ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/presetMultipleReg.o: libModbusRtu/presetMultipleReg.c  .generated_files/flags/default/3de307f060f8cb7ffe63505728a0fd4a8cdc64c0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/presetMultipleReg.c  -o ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/presetMultipleReg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/presetSingleReg.o: libModbusRtu/presetSingleReg.c  .generated_files/flags/default/d72fcfb31da7daaad88e4e4297cbacd613457bd1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetSingleReg.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetSingleReg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/presetSingleReg.c  -o ${OBJECTDIR}/libModbusRtu/presetSingleReg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/presetSingleReg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/readHoldingReg.o: libModbusRtu/readHoldingReg.c  .generated_files/flags/default/87c05ca28b35fa8b1a7619e7902c30d4a739e234 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/readHoldingReg.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/readHoldingReg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/readHoldingReg.c  -o ${OBJECTDIR}/libModbusRtu/readHoldingReg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/readHoldingReg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/fe5d98d754766aa901243800c87158af48694d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/libModbusRtu/crcRTU.o: libModbusRtu/crcRTU.c  .generated_files/flags/default/fcac2a4fec9e473862b051377cb051612ba26df1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/crcRTU.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/crcRTU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/crcRTU.c  -o ${OBJECTDIR}/libModbusRtu/crcRTU.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/crcRTU.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/modbusRtuError.o: libModbusRtu/modbusRtuError.c  .generated_files/flags/default/3b0b4720f05fc344204db114e8a92aafd43335e3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuError.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuError.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/modbusRtuError.c  -o ${OBJECTDIR}/libModbusRtu/modbusRtuError.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/modbusRtuError.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o: libModbusRtu/modbusRtuFrame.c  .generated_files/flags/default/7192c6dd8e9bdfb1d4cc15c4a46241989a8a120a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/modbusRtuFrame.c  -o ${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/modbusRtuFrame.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o: libModbusRtu/modbusRtuPacketParse.c  .generated_files/flags/default/a9c029a77fcc343115cc1e8f7e06453672dbc3c5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/modbusRtuPacketParse.c  -o ${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/modbusRtuPacketParse.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/presetMultipleReg.o: libModbusRtu/presetMultipleReg.c  .generated_files/flags/default/4d261d8aa000765f0e18398d8440cf76447af5cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/presetMultipleReg.c  -o ${OBJECTDIR}/libModbusRtu/presetMultipleReg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/presetMultipleReg.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/presetSingleReg.o: libModbusRtu/presetSingleReg.c  .generated_files/flags/default/6ae3280b2df172acf55ea97097a464f6c69a81d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetSingleReg.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/presetSingleReg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/presetSingleReg.c  -o ${OBJECTDIR}/libModbusRtu/presetSingleReg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/presetSingleReg.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/libModbusRtu/readHoldingReg.o: libModbusRtu/readHoldingReg.c  .generated_files/flags/default/1878cb786a2b0f08bc7b88526c8db1a152fd67e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/libModbusRtu" 
	@${RM} ${OBJECTDIR}/libModbusRtu/readHoldingReg.o.d 
	@${RM} ${OBJECTDIR}/libModbusRtu/readHoldingReg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  libModbusRtu/readHoldingReg.c  -o ${OBJECTDIR}/libModbusRtu/readHoldingReg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/libModbusRtu/readHoldingReg.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4641d0cfa87d9bc9286f640b0ef203ac5df5c65f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Modbus_RTU_WT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
