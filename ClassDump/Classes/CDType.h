// -*- mode: ObjC -*-

//  This file is part of class-dump, a utility for examining the Objective-C segment of Mach-O files.
//  Copyright (C) 1997-2019 Steve Nygard.

#import <Foundation/Foundation.h>

@class CDTypeController, CDTypeFormatter, CDTypeName;

@interface CDType : NSObject <NSCopying>

@property (strong) NSString *variableName;

@property (nonatomic, readonly) int primitiveType;
@property (nonatomic, readonly) BOOL isIDType;
@property (nonatomic, readonly) BOOL isNamedObject;
@property (nonatomic, readonly) BOOL isTemplateType;

@property (nonatomic, readonly) CDType *subtype;
@property (nonatomic, readonly) CDTypeName *typeName;

@property (nonatomic, readonly) NSArray *members;
@property (nonatomic, readonly) NSArray *types;

@property (nonatomic, readonly) int typeIgnoringModifiers;
@property (nonatomic, readonly) NSUInteger structureDepth;

- (NSString *)formattedString:(NSString *)previousName formatter:(CDTypeFormatter *)typeFormatter level:(NSUInteger)level;

@property (nonatomic, readonly) NSString *typeString;
@property (nonatomic, readonly) NSString *bareTypeString;
@property (nonatomic, readonly) NSString *reallyBareTypeString;
@property (nonatomic, readonly) NSString *keyTypeString;

- (instancetype)initSimpleType:(int)type;
- (instancetype)initIDType:(CDTypeName *)name;
- (instancetype)initIDType:(CDTypeName *)name withProtocols:(NSArray *)protocols;
- (instancetype)initIDTypeWithProtocols:(NSArray *)protocols;
- (instancetype)initStructType:(CDTypeName *)name members:(NSArray *)members;
- (instancetype)initUnionType:(CDTypeName *)name members:(NSArray *)members;
- (instancetype)initBitfieldType:(NSString *)bitfieldSize;
- (instancetype)initArrayType:(CDType *)type count:(NSString *)count;
- (instancetype)initPointerType:(CDType *)type;
- (instancetype)initFunctionPointerType;
- (instancetype)initBlockTypeWithTypes:(NSArray *)types;
- (instancetype)initModifier:(int)modifier type:(CDType *)type;

- (BOOL)canMergeWithType:(CDType *)otherType;
- (void)mergeWithType:(CDType *)otherType;

@property (nonatomic, readonly) NSArray *memberVariableNames;
- (void)generateMemberNames;

// Phase 0
- (void)phase:(NSUInteger)phase registerTypesWithObject:(CDTypeController *)typeController usedInMethod:(BOOL)isUsedInMethod;
- (void)phase0RecursivelyFixStructureNames:(BOOL)flag;

// Phase 1
- (void)phase1RegisterStructuresWithObject:(CDTypeController *)typeController;

// Phase 2
- (void)phase2MergeWithTypeController:(CDTypeController *)typeController debug:(BOOL)phase2Debug;

// Phase 3
- (void)phase3RegisterMembersWithTypeController:(CDTypeController *)typeController;
- (void)phase3MergeWithTypeController:(CDTypeController *)typeController;

@end
