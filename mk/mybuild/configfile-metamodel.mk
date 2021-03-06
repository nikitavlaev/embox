# Generated by Xpand using M2Make template.

# Meta model for 'configFile' package.

ifndef __mybuild_configfile_metamodel_mk
__mybuild_configfile_metamodel_mk := 1

include mk/model/metamodel_impl.mk

# Create meta objects.
ConfigFile := \
	$(call eMetaModelCreate,ConfigFile)

ConfigFile_FileContentRoot := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_FileContentRoot)
ConfigFile_FileContentRoot_configuration := \
	$(call eMetaReferenceCreate,$(ConfigFile_FileContentRoot),ConfigFile_FileContentRoot_configuration)
ConfigFile_FileContentRoot_imports := \
	$(call eMetaAttributeCreate,$(ConfigFile_FileContentRoot),ConfigFile_FileContentRoot_imports)

ConfigFile_Configuration := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_Configuration)
ConfigFile_Configuration_fileContentRoot := \
	$(call eMetaReferenceCreate,$(ConfigFile_Configuration),ConfigFile_Configuration_fileContentRoot)
ConfigFile_Configuration_includes := \
	$(call eMetaReferenceCreate,$(ConfigFile_Configuration),ConfigFile_Configuration_includes)

ConfigFile_Include := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_Include)
ConfigFile_Include_module := \
	$(call eMetaReferenceCreate,$(ConfigFile_Include),ConfigFile_Include_module)
ConfigFile_Include_optionBindings := \
	$(call eMetaReferenceCreate,$(ConfigFile_Include),ConfigFile_Include_optionBindings)

# Initializes the objects and relations between them.
define __configFile_init
	$(call eMetaModelInit,$(ConfigFile),configFile,cfg)

	$(call eMetaClassInit,$(ConfigFile_FileContentRoot),FileContentRoot,$(EModel_ENamedObject),)
	$(call eMetaReferenceInit,$(ConfigFile_FileContentRoot_configuration),configuration,$(ConfigFile_Configuration),$(ConfigFile_Configuration_fileContentRoot),changeable containment)
	$(call eMetaAttributeInit,$(ConfigFile_FileContentRoot_imports),imports,changeable many)

	$(call eMetaClassInit,$(ConfigFile_Configuration),Configuration,$(EModel_ENamedObject) $(MyFile_AnnotationTarget),)
	$(call eMetaReferenceInit,$(ConfigFile_Configuration_fileContentRoot),fileContentRoot,$(ConfigFile_FileContentRoot),$(ConfigFile_FileContentRoot_configuration),changeable container)
	$(call eMetaReferenceInit,$(ConfigFile_Configuration_includes),includes,$(ConfigFile_Include),,changeable many containment)

	$(call eMetaClassInit,$(ConfigFile_Include),Include,$(MyFile_AnnotationTarget) $(EModel_ENamedObject),)
	$(call eMetaReferenceInit,$(ConfigFile_Include_module),module,$(MyFile_ModuleType),,changeable many linkable)
	$(call eMetaReferenceInit,$(ConfigFile_Include_optionBindings),optionBindings,$(MyFile_OptionBinding),,changeable many containment)

endef # __configFile_init

# Binds objects to instance classes and features to properties.
define __configFile_bind
	$(call eMetaClassBind,$(ConfigFile_FileContentRoot),CfgFileContentRoot)
	$(call eMetaFeatureBind,$(ConfigFile_FileContentRoot_configuration),configuration)
	$(call eMetaFeatureBind,$(ConfigFile_FileContentRoot_imports),imports)

	$(call eMetaClassBind,$(ConfigFile_Configuration),CfgConfiguration)
	$(call eMetaFeatureBind,$(ConfigFile_Configuration_fileContentRoot),fileContentRoot)
	$(call eMetaFeatureBind,$(ConfigFile_Configuration_includes),includes)

	$(call eMetaClassBind,$(ConfigFile_Include),CfgInclude)
	$(call eMetaFeatureBind,$(ConfigFile_Include_module),module)
	$(call eMetaFeatureBind,$(ConfigFile_Include_optionBindings),optionBindings)

endef # __configFile_bind

$(def_all)

$(call __configFile_init)
$(call __configFile_bind)

$(call eMetaModelFreeze,$(ConfigFile))

endif # __mybuild_configfile_metamodel_mk

