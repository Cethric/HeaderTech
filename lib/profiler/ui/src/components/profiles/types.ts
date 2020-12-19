export type CpuProfileHash = number;

export enum ScopedProfilerFlags {
    None = "none",
    Aggregate = "aggregate",
    Recursive = "recursive",
}

export interface CpuProfile {
    name: string;
    function: string;
    line: string;
    file: string;
    flags: ScopedProfilerFlags;
    call_count: number;
    max_recursion_count: number;
    delta: number;
    total_delta: number;
    parent: number;
    start: number;
    end: number;
    children: CpuProfileHash[];
}

export type CpuProfileRecord = [CpuProfileHash, CpuProfile];
export type CpuProfileMap = CpuProfileRecord[];

export interface CpuProfileResult {
    id: CpuProfileHash;
    name: string;
    delta: number;
    children: CpuProfileResult[];
    start: number;
    end: number;
}

const getCpuProfileChildren = (data: CpuProfileMap, children: CpuProfileHash[]): CpuProfileRecord[] => {
    return children.map((childId) => data[data.findIndex(([id]) => id === childId)]);
};

const processCpuProfileData = (data: CpuProfileMap, targets: CpuProfileHash[]): CpuProfileResult[] => {
    return getCpuProfileChildren(data, targets).map<CpuProfileResult>(([id, profile]) => ({
        id,
        name: profile.name,
        delta: profile.delta,
        start: profile.start,
        end: profile.end,
        children: processCpuProfileData(data, profile.children),
    }));
};

export const prepareCpuProfileData = (data: CpuProfileMap): CpuProfileResult[] => {
    const [[_, root]] = getCpuProfileChildren(data, [0]);
    return processCpuProfileData(data, root.children);
};
