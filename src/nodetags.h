
case T_List: printf("List"); break;
case T_Alias: printf("Alias"); break;
case T_RangeVar: printf("RangeVar"); break;
case T_TableFunc: printf("TableFunc"); break;
case T_IntoClause: printf("IntoClause"); break;
case T_Var: printf("Var"); break;
case T_Const: printf("Const"); break;
case T_Param: printf("Param"); break;
case T_Aggref: printf("Aggref"); break;
case T_GroupingFunc: printf("GroupingFunc"); break;
case T_WindowFunc: printf("WindowFunc"); break;
case T_SubscriptingRef: printf("SubscriptingRef"); break;
case T_FuncExpr: printf("FuncExpr"); break;
case T_NamedArgExpr: printf("NamedArgExpr"); break;
case T_OpExpr: printf("OpExpr"); break;
case T_DistinctExpr: printf("DistinctExpr"); break;
case T_NullIfExpr: printf("NullIfExpr"); break;
case T_ScalarArrayOpExpr: printf("ScalarArrayOpExpr"); break;
case T_BoolExpr: printf("BoolExpr"); break;
case T_SubLink: printf("SubLink"); break;
case T_SubPlan: printf("SubPlan"); break;
case T_AlternativeSubPlan: printf("AlternativeSubPlan"); break;
case T_FieldSelect: printf("FieldSelect"); break;
case T_FieldStore: printf("FieldStore"); break;
case T_RelabelType: printf("RelabelType"); break;
case T_CoerceViaIO: printf("CoerceViaIO"); break;
case T_ArrayCoerceExpr: printf("ArrayCoerceExpr"); break;
case T_ConvertRowtypeExpr: printf("ConvertRowtypeExpr"); break;
case T_CollateExpr: printf("CollateExpr"); break;
case T_CaseExpr: printf("CaseExpr"); break;
case T_CaseWhen: printf("CaseWhen"); break;
case T_CaseTestExpr: printf("CaseTestExpr"); break;
case T_ArrayExpr: printf("ArrayExpr"); break;
case T_RowExpr: printf("RowExpr"); break;
case T_RowCompareExpr: printf("RowCompareExpr"); break;
case T_CoalesceExpr: printf("CoalesceExpr"); break;
case T_MinMaxExpr: printf("MinMaxExpr"); break;
case T_SQLValueFunction: printf("SQLValueFunction"); break;
case T_XmlExpr: printf("XmlExpr"); break;
case T_JsonFormat: printf("JsonFormat"); break;
case T_JsonReturning: printf("JsonReturning"); break;
case T_JsonValueExpr: printf("JsonValueExpr"); break;
case T_JsonConstructorExpr: printf("JsonConstructorExpr"); break;
case T_JsonIsPredicate: printf("JsonIsPredicate"); break;
case T_NullTest: printf("NullTest"); break;
case T_BooleanTest: printf("BooleanTest"); break;
case T_CoerceToDomain: printf("CoerceToDomain"); break;
case T_CoerceToDomainValue: printf("CoerceToDomainValue"); break;
case T_SetToDefault: printf("SetToDefault"); break;
case T_CurrentOfExpr: printf("CurrentOfExpr"); break;
case T_NextValueExpr: printf("NextValueExpr"); break;
case T_InferenceElem: printf("InferenceElem"); break;
case T_TargetEntry: printf("TargetEntry"); break;
case T_RangeTblRef: printf("RangeTblRef"); break;
case T_JoinExpr: printf("JoinExpr"); break;
case T_FromExpr: printf("FromExpr"); break;
case T_OnConflictExpr: printf("OnConflictExpr"); break;
case T_Query: printf("Query"); break;
case T_TypeName: printf("TypeName"); break;
case T_ColumnRef: printf("ColumnRef"); break;
case T_ParamRef: printf("ParamRef"); break;
case T_A_Expr: printf("A_Expr"); break;
case T_A_Const: printf("A_Const"); break;
case T_TypeCast: printf("TypeCast"); break;
case T_CollateClause: printf("CollateClause"); break;
case T_RoleSpec: printf("RoleSpec"); break;
case T_FuncCall: printf("FuncCall"); break;
case T_A_Star: printf("A_Star"); break;
case T_A_Indices: printf("A_Indices"); break;
case T_A_Indirection: printf("A_Indirection"); break;
case T_A_ArrayExpr: printf("A_ArrayExpr"); break;
case T_ResTarget: printf("ResTarget"); break;
case T_MultiAssignRef: printf("MultiAssignRef"); break;
case T_SortBy: printf("SortBy"); break;
case T_WindowDef: printf("WindowDef"); break;
case T_RangeSubselect: printf("RangeSubselect"); break;
case T_RangeFunction: printf("RangeFunction"); break;
case T_RangeTableFunc: printf("RangeTableFunc"); break;
case T_RangeTableFuncCol: printf("RangeTableFuncCol"); break;
case T_RangeTableSample: printf("RangeTableSample"); break;
case T_ColumnDef: printf("ColumnDef"); break;
case T_TableLikeClause: printf("TableLikeClause"); break;
case T_IndexElem: printf("IndexElem"); break;
case T_DefElem: printf("DefElem"); break;
case T_LockingClause: printf("LockingClause"); break;
case T_XmlSerialize: printf("XmlSerialize"); break;
case T_PartitionElem: printf("PartitionElem"); break;
case T_PartitionSpec: printf("PartitionSpec"); break;
case T_PartitionBoundSpec: printf("PartitionBoundSpec"); break;
case T_PartitionRangeDatum: printf("PartitionRangeDatum"); break;
case T_PartitionCmd: printf("PartitionCmd"); break;
case T_RangeTblEntry: printf("RangeTblEntry"); break;
case T_RTEPermissionInfo: printf("RTEPermissionInfo"); break;
case T_RangeTblFunction: printf("RangeTblFunction"); break;
case T_TableSampleClause: printf("TableSampleClause"); break;
case T_WithCheckOption: printf("WithCheckOption"); break;
case T_SortGroupClause: printf("SortGroupClause"); break;
case T_GroupingSet: printf("GroupingSet"); break;
case T_WindowClause: printf("WindowClause"); break;
case T_RowMarkClause: printf("RowMarkClause"); break;
case T_WithClause: printf("WithClause"); break;
case T_InferClause: printf("InferClause"); break;
case T_OnConflictClause: printf("OnConflictClause"); break;
case T_CTESearchClause: printf("CTESearchClause"); break;
case T_CTECycleClause: printf("CTECycleClause"); break;
case T_CommonTableExpr: printf("CommonTableExpr"); break;
case T_MergeWhenClause: printf("MergeWhenClause"); break;
case T_MergeAction: printf("MergeAction"); break;
case T_TriggerTransition: printf("TriggerTransition"); break;
case T_JsonOutput: printf("JsonOutput"); break;
case T_JsonKeyValue: printf("JsonKeyValue"); break;
case T_JsonObjectConstructor: printf("JsonObjectConstructor"); break;
case T_JsonArrayConstructor: printf("JsonArrayConstructor"); break;
case T_JsonArrayQueryConstructor: printf("JsonArrayQueryConstructor"); break;
case T_JsonAggConstructor: printf("JsonAggConstructor"); break;
case T_JsonObjectAgg: printf("JsonObjectAgg"); break;
case T_JsonArrayAgg: printf("JsonArrayAgg"); break;
case T_RawStmt: printf("RawStmt"); break;
case T_InsertStmt: printf("InsertStmt"); break;
case T_DeleteStmt: printf("DeleteStmt"); break;
case T_UpdateStmt: printf("UpdateStmt"); break;
case T_MergeStmt: printf("MergeStmt"); break;
case T_SelectStmt: printf("SelectStmt"); break;
case T_SetOperationStmt: printf("SetOperationStmt"); break;
case T_ReturnStmt: printf("ReturnStmt"); break;
case T_PLAssignStmt: printf("PLAssignStmt"); break;
case T_CreateSchemaStmt: printf("CreateSchemaStmt"); break;
case T_AlterTableStmt: printf("AlterTableStmt"); break;
case T_ReplicaIdentityStmt: printf("ReplicaIdentityStmt"); break;
case T_AlterTableCmd: printf("AlterTableCmd"); break;
case T_AlterCollationStmt: printf("AlterCollationStmt"); break;
case T_AlterDomainStmt: printf("AlterDomainStmt"); break;
case T_GrantStmt: printf("GrantStmt"); break;
case T_ObjectWithArgs: printf("ObjectWithArgs"); break;
case T_AccessPriv: printf("AccessPriv"); break;
case T_GrantRoleStmt: printf("GrantRoleStmt"); break;
case T_AlterDefaultPrivilegesStmt: printf("AlterDefaultPrivilegesStmt"); break;
case T_CopyStmt: printf("CopyStmt"); break;
case T_VariableSetStmt: printf("VariableSetStmt"); break;
case T_VariableShowStmt: printf("VariableShowStmt"); break;
case T_CreateStmt: printf("CreateStmt"); break;
case T_Constraint: printf("Constraint"); break;
case T_CreateTableSpaceStmt: printf("CreateTableSpaceStmt"); break;
case T_DropTableSpaceStmt: printf("DropTableSpaceStmt"); break;
case T_AlterTableSpaceOptionsStmt: printf("AlterTableSpaceOptionsStmt"); break;
case T_AlterTableMoveAllStmt: printf("AlterTableMoveAllStmt"); break;
case T_CreateExtensionStmt: printf("CreateExtensionStmt"); break;
case T_AlterExtensionStmt: printf("AlterExtensionStmt"); break;
case T_AlterExtensionContentsStmt: printf("AlterExtensionContentsStmt"); break;
case T_CreateFdwStmt: printf("CreateFdwStmt"); break;
case T_AlterFdwStmt: printf("AlterFdwStmt"); break;
case T_CreateForeignServerStmt: printf("CreateForeignServerStmt"); break;
case T_AlterForeignServerStmt: printf("AlterForeignServerStmt"); break;
case T_CreateForeignTableStmt: printf("CreateForeignTableStmt"); break;
case T_CreateUserMappingStmt: printf("CreateUserMappingStmt"); break;
case T_AlterUserMappingStmt: printf("AlterUserMappingStmt"); break;
case T_DropUserMappingStmt: printf("DropUserMappingStmt"); break;
case T_ImportForeignSchemaStmt: printf("ImportForeignSchemaStmt"); break;
case T_CreatePolicyStmt: printf("CreatePolicyStmt"); break;
case T_AlterPolicyStmt: printf("AlterPolicyStmt"); break;
case T_CreateAmStmt: printf("CreateAmStmt"); break;
case T_CreateTrigStmt: printf("CreateTrigStmt"); break;
case T_CreateEventTrigStmt: printf("CreateEventTrigStmt"); break;
case T_AlterEventTrigStmt: printf("AlterEventTrigStmt"); break;
case T_CreatePLangStmt: printf("CreatePLangStmt"); break;
case T_CreateRoleStmt: printf("CreateRoleStmt"); break;
case T_AlterRoleStmt: printf("AlterRoleStmt"); break;
case T_AlterRoleSetStmt: printf("AlterRoleSetStmt"); break;
case T_DropRoleStmt: printf("DropRoleStmt"); break;
case T_CreateSeqStmt: printf("CreateSeqStmt"); break;
case T_AlterSeqStmt: printf("AlterSeqStmt"); break;
case T_DefineStmt: printf("DefineStmt"); break;
case T_CreateDomainStmt: printf("CreateDomainStmt"); break;
case T_CreateOpClassStmt: printf("CreateOpClassStmt"); break;
case T_CreateOpClassItem: printf("CreateOpClassItem"); break;
case T_CreateOpFamilyStmt: printf("CreateOpFamilyStmt"); break;
case T_AlterOpFamilyStmt: printf("AlterOpFamilyStmt"); break;
case T_DropStmt: printf("DropStmt"); break;
case T_TruncateStmt: printf("TruncateStmt"); break;
case T_CommentStmt: printf("CommentStmt"); break;
case T_SecLabelStmt: printf("SecLabelStmt"); break;
case T_DeclareCursorStmt: printf("DeclareCursorStmt"); break;
case T_ClosePortalStmt: printf("ClosePortalStmt"); break;
case T_FetchStmt: printf("FetchStmt"); break;
case T_IndexStmt: printf("IndexStmt"); break;
case T_CreateStatsStmt: printf("CreateStatsStmt"); break;
case T_StatsElem: printf("StatsElem"); break;
case T_AlterStatsStmt: printf("AlterStatsStmt"); break;
case T_CreateFunctionStmt: printf("CreateFunctionStmt"); break;
case T_FunctionParameter: printf("FunctionParameter"); break;
case T_AlterFunctionStmt: printf("AlterFunctionStmt"); break;
case T_DoStmt: printf("DoStmt"); break;
case T_InlineCodeBlock: printf("InlineCodeBlock"); break;
case T_CallStmt: printf("CallStmt"); break;
case T_CallContext: printf("CallContext"); break;
case T_RenameStmt: printf("RenameStmt"); break;
case T_AlterObjectDependsStmt: printf("AlterObjectDependsStmt"); break;
case T_AlterObjectSchemaStmt: printf("AlterObjectSchemaStmt"); break;
case T_AlterOwnerStmt: printf("AlterOwnerStmt"); break;
case T_AlterOperatorStmt: printf("AlterOperatorStmt"); break;
case T_AlterTypeStmt: printf("AlterTypeStmt"); break;
case T_RuleStmt: printf("RuleStmt"); break;
case T_NotifyStmt: printf("NotifyStmt"); break;
case T_ListenStmt: printf("ListenStmt"); break;
case T_UnlistenStmt: printf("UnlistenStmt"); break;
case T_TransactionStmt: printf("TransactionStmt"); break;
case T_CompositeTypeStmt: printf("CompositeTypeStmt"); break;
case T_CreateEnumStmt: printf("CreateEnumStmt"); break;
case T_CreateRangeStmt: printf("CreateRangeStmt"); break;
case T_AlterEnumStmt: printf("AlterEnumStmt"); break;
case T_ViewStmt: printf("ViewStmt"); break;
case T_LoadStmt: printf("LoadStmt"); break;
case T_CreatedbStmt: printf("CreatedbStmt"); break;
case T_AlterDatabaseStmt: printf("AlterDatabaseStmt"); break;
case T_AlterDatabaseRefreshCollStmt: printf("AlterDatabaseRefreshCollStmt"); break;
case T_AlterDatabaseSetStmt: printf("AlterDatabaseSetStmt"); break;
case T_DropdbStmt: printf("DropdbStmt"); break;
case T_AlterSystemStmt: printf("AlterSystemStmt"); break;
case T_ClusterStmt: printf("ClusterStmt"); break;
case T_VacuumStmt: printf("VacuumStmt"); break;
case T_VacuumRelation: printf("VacuumRelation"); break;
case T_ExplainStmt: printf("ExplainStmt"); break;
case T_CreateTableAsStmt: printf("CreateTableAsStmt"); break;
case T_RefreshMatViewStmt: printf("RefreshMatViewStmt"); break;
case T_CheckPointStmt: printf("CheckPointStmt"); break;
case T_DiscardStmt: printf("DiscardStmt"); break;
case T_LockStmt: printf("LockStmt"); break;
case T_ConstraintsSetStmt: printf("ConstraintsSetStmt"); break;
case T_ReindexStmt: printf("ReindexStmt"); break;
case T_CreateConversionStmt: printf("CreateConversionStmt"); break;
case T_CreateCastStmt: printf("CreateCastStmt"); break;
case T_CreateTransformStmt: printf("CreateTransformStmt"); break;
case T_PrepareStmt: printf("PrepareStmt"); break;
case T_ExecuteStmt: printf("ExecuteStmt"); break;
case T_DeallocateStmt: printf("DeallocateStmt"); break;
case T_DropOwnedStmt: printf("DropOwnedStmt"); break;
case T_ReassignOwnedStmt: printf("ReassignOwnedStmt"); break;
case T_AlterTSDictionaryStmt: printf("AlterTSDictionaryStmt"); break;
case T_AlterTSConfigurationStmt: printf("AlterTSConfigurationStmt"); break;
case T_PublicationTable: printf("PublicationTable"); break;
case T_PublicationObjSpec: printf("PublicationObjSpec"); break;
case T_CreatePublicationStmt: printf("CreatePublicationStmt"); break;
case T_AlterPublicationStmt: printf("AlterPublicationStmt"); break;
case T_CreateSubscriptionStmt: printf("CreateSubscriptionStmt"); break;
case T_AlterSubscriptionStmt: printf("AlterSubscriptionStmt"); break;
case T_DropSubscriptionStmt: printf("DropSubscriptionStmt"); break;
case T_PlannerGlobal: printf("PlannerGlobal"); break;
case T_PlannerInfo: printf("PlannerInfo"); break;
case T_RelOptInfo: printf("RelOptInfo"); break;
case T_IndexOptInfo: printf("IndexOptInfo"); break;
case T_ForeignKeyOptInfo: printf("ForeignKeyOptInfo"); break;
case T_StatisticExtInfo: printf("StatisticExtInfo"); break;
case T_JoinDomain: printf("JoinDomain"); break;
case T_EquivalenceClass: printf("EquivalenceClass"); break;
case T_EquivalenceMember: printf("EquivalenceMember"); break;
case T_PathKey: printf("PathKey"); break;
case T_PathTarget: printf("PathTarget"); break;
case T_ParamPathInfo: printf("ParamPathInfo"); break;
case T_Path: printf("Path"); break;
case T_IndexPath: printf("IndexPath"); break;
case T_IndexClause: printf("IndexClause"); break;
case T_BitmapHeapPath: printf("BitmapHeapPath"); break;
case T_BitmapAndPath: printf("BitmapAndPath"); break;
case T_BitmapOrPath: printf("BitmapOrPath"); break;
case T_TidPath: printf("TidPath"); break;
case T_TidRangePath: printf("TidRangePath"); break;
case T_SubqueryScanPath: printf("SubqueryScanPath"); break;
case T_ForeignPath: printf("ForeignPath"); break;
case T_CustomPath: printf("CustomPath"); break;
case T_AppendPath: printf("AppendPath"); break;
case T_MergeAppendPath: printf("MergeAppendPath"); break;
case T_GroupResultPath: printf("GroupResultPath"); break;
case T_MaterialPath: printf("MaterialPath"); break;
case T_MemoizePath: printf("MemoizePath"); break;
case T_UniquePath: printf("UniquePath"); break;
case T_GatherPath: printf("GatherPath"); break;
case T_GatherMergePath: printf("GatherMergePath"); break;
case T_NestPath: printf("NestPath"); break;
case T_MergePath: printf("MergePath"); break;
case T_HashPath: printf("HashPath"); break;
case T_ProjectionPath: printf("ProjectionPath"); break;
case T_ProjectSetPath: printf("ProjectSetPath"); break;
case T_SortPath: printf("SortPath"); break;
case T_IncrementalSortPath: printf("IncrementalSortPath"); break;
case T_GroupPath: printf("GroupPath"); break;
case T_UpperUniquePath: printf("UpperUniquePath"); break;
case T_AggPath: printf("AggPath"); break;
case T_GroupingSetData: printf("GroupingSetData"); break;
case T_RollupData: printf("RollupData"); break;
case T_GroupingSetsPath: printf("GroupingSetsPath"); break;
case T_MinMaxAggPath: printf("MinMaxAggPath"); break;
case T_WindowAggPath: printf("WindowAggPath"); break;
case T_SetOpPath: printf("SetOpPath"); break;
case T_RecursiveUnionPath: printf("RecursiveUnionPath"); break;
case T_LockRowsPath: printf("LockRowsPath"); break;
case T_ModifyTablePath: printf("ModifyTablePath"); break;
case T_LimitPath: printf("LimitPath"); break;
case T_RestrictInfo: printf("RestrictInfo"); break;
case T_PlaceHolderVar: printf("PlaceHolderVar"); break;
case T_SpecialJoinInfo: printf("SpecialJoinInfo"); break;
case T_OuterJoinClauseInfo: printf("OuterJoinClauseInfo"); break;
case T_AppendRelInfo: printf("AppendRelInfo"); break;
case T_RowIdentityVarInfo: printf("RowIdentityVarInfo"); break;
case T_PlaceHolderInfo: printf("PlaceHolderInfo"); break;
case T_MinMaxAggInfo: printf("MinMaxAggInfo"); break;
case T_PlannerParamItem: printf("PlannerParamItem"); break;
case T_AggInfo: printf("AggInfo"); break;
case T_AggTransInfo: printf("AggTransInfo"); break;
case T_PlannedStmt: printf("PlannedStmt"); break;
case T_Result: printf("Result"); break;
case T_ProjectSet: printf("ProjectSet"); break;
case T_ModifyTable: printf("ModifyTable"); break;
case T_Append: printf("Append"); break;
case T_MergeAppend: printf("MergeAppend"); break;
case T_RecursiveUnion: printf("RecursiveUnion"); break;
case T_BitmapAnd: printf("BitmapAnd"); break;
case T_BitmapOr: printf("BitmapOr"); break;
case T_SeqScan: printf("SeqScan"); break;
case T_SampleScan: printf("SampleScan"); break;
case T_IndexScan: printf("IndexScan"); break;
case T_IndexOnlyScan: printf("IndexOnlyScan"); break;
case T_BitmapIndexScan: printf("BitmapIndexScan"); break;
case T_BitmapHeapScan: printf("BitmapHeapScan"); break;
case T_TidScan: printf("TidScan"); break;
case T_TidRangeScan: printf("TidRangeScan"); break;
case T_SubqueryScan: printf("SubqueryScan"); break;
case T_FunctionScan: printf("FunctionScan"); break;
case T_ValuesScan: printf("ValuesScan"); break;
case T_TableFuncScan: printf("TableFuncScan"); break;
case T_CteScan: printf("CteScan"); break;
case T_NamedTuplestoreScan: printf("NamedTuplestoreScan"); break;
case T_WorkTableScan: printf("WorkTableScan"); break;
case T_ForeignScan: printf("ForeignScan"); break;
case T_CustomScan: printf("CustomScan"); break;
case T_NestLoop: printf("NestLoop"); break;
case T_NestLoopParam: printf("NestLoopParam"); break;
case T_MergeJoin: printf("MergeJoin"); break;
case T_HashJoin: printf("HashJoin"); break;
case T_Material: printf("Material"); break;
case T_Memoize: printf("Memoize"); break;
case T_Sort: printf("Sort"); break;
case T_IncrementalSort: printf("IncrementalSort"); break;
case T_Group: printf("Group"); break;
case T_Agg: printf("Agg"); break;
case T_WindowAgg: printf("WindowAgg"); break;
case T_Unique: printf("Unique"); break;
case T_Gather: printf("Gather"); break;
case T_GatherMerge: printf("GatherMerge"); break;
case T_Hash: printf("Hash"); break;
case T_SetOp: printf("SetOp"); break;
case T_LockRows: printf("LockRows"); break;
case T_Limit: printf("Limit"); break;
case T_PlanRowMark: printf("PlanRowMark"); break;
case T_PartitionPruneInfo: printf("PartitionPruneInfo"); break;
case T_PartitionedRelPruneInfo: printf("PartitionedRelPruneInfo"); break;
case T_PartitionPruneStepOp: printf("PartitionPruneStepOp"); break;
case T_PartitionPruneStepCombine: printf("PartitionPruneStepCombine"); break;
case T_PlanInvalItem: printf("PlanInvalItem"); break;
case T_ExprState: printf("ExprState"); break;
case T_IndexInfo: printf("IndexInfo"); break;
case T_ExprContext: printf("ExprContext"); break;
case T_ReturnSetInfo: printf("ReturnSetInfo"); break;
case T_ProjectionInfo: printf("ProjectionInfo"); break;
case T_JunkFilter: printf("JunkFilter"); break;
case T_OnConflictSetState: printf("OnConflictSetState"); break;
case T_MergeActionState: printf("MergeActionState"); break;
case T_ResultRelInfo: printf("ResultRelInfo"); break;
case T_EState: printf("EState"); break;
case T_WindowFuncExprState: printf("WindowFuncExprState"); break;
case T_SetExprState: printf("SetExprState"); break;
case T_SubPlanState: printf("SubPlanState"); break;
case T_DomainConstraintState: printf("DomainConstraintState"); break;
case T_ResultState: printf("ResultState"); break;
case T_ProjectSetState: printf("ProjectSetState"); break;
case T_ModifyTableState: printf("ModifyTableState"); break;
case T_AppendState: printf("AppendState"); break;
case T_MergeAppendState: printf("MergeAppendState"); break;
case T_RecursiveUnionState: printf("RecursiveUnionState"); break;
case T_BitmapAndState: printf("BitmapAndState"); break;
case T_BitmapOrState: printf("BitmapOrState"); break;
case T_ScanState: printf("ScanState"); break;
case T_SeqScanState: printf("SeqScanState"); break;
case T_SampleScanState: printf("SampleScanState"); break;
case T_IndexScanState: printf("IndexScanState"); break;
case T_IndexOnlyScanState: printf("IndexOnlyScanState"); break;
case T_BitmapIndexScanState: printf("BitmapIndexScanState"); break;
case T_BitmapHeapScanState: printf("BitmapHeapScanState"); break;
case T_TidScanState: printf("TidScanState"); break;
case T_TidRangeScanState: printf("TidRangeScanState"); break;
case T_SubqueryScanState: printf("SubqueryScanState"); break;
case T_FunctionScanState: printf("FunctionScanState"); break;
case T_ValuesScanState: printf("ValuesScanState"); break;
case T_TableFuncScanState: printf("TableFuncScanState"); break;
case T_CteScanState: printf("CteScanState"); break;
case T_NamedTuplestoreScanState: printf("NamedTuplestoreScanState"); break;
case T_WorkTableScanState: printf("WorkTableScanState"); break;
case T_ForeignScanState: printf("ForeignScanState"); break;
case T_CustomScanState: printf("CustomScanState"); break;
case T_JoinState: printf("JoinState"); break;
case T_NestLoopState: printf("NestLoopState"); break;
case T_MergeJoinState: printf("MergeJoinState"); break;
case T_HashJoinState: printf("HashJoinState"); break;
case T_MaterialState: printf("MaterialState"); break;
case T_MemoizeState: printf("MemoizeState"); break;
case T_SortState: printf("SortState"); break;
case T_IncrementalSortState: printf("IncrementalSortState"); break;
case T_GroupState: printf("GroupState"); break;
case T_AggState: printf("AggState"); break;
case T_WindowAggState: printf("WindowAggState"); break;
case T_UniqueState: printf("UniqueState"); break;
case T_GatherState: printf("GatherState"); break;
case T_GatherMergeState: printf("GatherMergeState"); break;
case T_HashState: printf("HashState"); break;
case T_SetOpState: printf("SetOpState"); break;
case T_LockRowsState: printf("LockRowsState"); break;
case T_LimitState: printf("LimitState"); break;
case T_IndexAmRoutine: printf("IndexAmRoutine"); break;
case T_TableAmRoutine: printf("TableAmRoutine"); break;
case T_TsmRoutine: printf("TsmRoutine"); break;
case T_EventTriggerData: printf("EventTriggerData"); break;
case T_TriggerData: printf("TriggerData"); break;
case T_TupleTableSlot: printf("TupleTableSlot"); break;
case T_FdwRoutine: printf("FdwRoutine"); break;
case T_Bitmapset: printf("Bitmapset"); break;
case T_ExtensibleNode: printf("ExtensibleNode"); break;
case T_ErrorSaveContext: printf("ErrorSaveContext"); break;
case T_IdentifySystemCmd: printf("IdentifySystemCmd"); break;
case T_BaseBackupCmd: printf("BaseBackupCmd"); break;
case T_CreateReplicationSlotCmd: printf("CreateReplicationSlotCmd"); break;
case T_DropReplicationSlotCmd: printf("DropReplicationSlotCmd"); break;
case T_StartReplicationCmd: printf("StartReplicationCmd"); break;
case T_ReadReplicationSlotCmd: printf("ReadReplicationSlotCmd"); break;
case T_TimeLineHistoryCmd: printf("TimeLineHistoryCmd"); break;
case T_SupportRequestSimplify: printf("SupportRequestSimplify"); break;
case T_SupportRequestSelectivity: printf("SupportRequestSelectivity"); break;
case T_SupportRequestCost: printf("SupportRequestCost"); break;
case T_SupportRequestRows: printf("SupportRequestRows"); break;
case T_SupportRequestIndexCondition: printf("SupportRequestIndexCondition"); break;
case T_SupportRequestWFuncMonotonic: printf("SupportRequestWFuncMonotonic"); break;
case T_SupportRequestOptimizeWindowClause: printf("SupportRequestOptimizeWindowClause"); break;
case T_Integer: printf("Integer"); break;
case T_Float: printf("Float"); break;
case T_Boolean: printf("Boolean"); break;
case T_String: printf("String"); break;
case T_BitString: printf("BitString"); break;
case T_ForeignKeyCacheInfo: printf("ForeignKeyCacheInfo"); break;
case T_IntList: printf("IntList"); break;
case T_OidList: printf("OidList"); break;
case T_XidList: printf("XidList"); break;
case T_AllocSetContext: printf("AllocSetContext"); break;
case T_GenerationContext: printf("GenerationContext"); break;
case T_SlabContext: printf("SlabContext"); break;
case T_TIDBitmap: printf("TIDBitmap"); break;
case T_WindowObjectData: printf("WindowObjectData"); break;

