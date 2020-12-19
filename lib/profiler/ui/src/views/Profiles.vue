<template>
  <b-container class="profiles">
    <b-row>
      <b-col cols="12">
        <MultilevelTreeMap :data="current" />
      </b-col>
    </b-row>
    <b-row>
      <b-col cols="12">
        <Waterfall :data="current" />
      </b-col>
    </b-row>
    <b-row>
      <!--      <TimingMarksTable :marks="history" />-->
    </b-row>
  </b-container>
</template>

<style lang="scss" scoped></style>

<script lang="ts">
import { Component, Vue } from "vue-property-decorator";
import TimingMarksTable from "@/components/profiles/TimingMarksTable.vue";
import { CpuProfileResult, prepareCpuProfileData } from "@/components/profiles/types";
import MultilevelTreeMap from "@/components/profiles/MultilevelTreeMap.vue";
import Waterfall from "@/components/profiles/Waterfall.vue";

@Component({
  components: { Waterfall, MultilevelTreeMap, TimingMarksTable }
})
export default class Profiles extends Vue {
  private readonly profileSource: EventSource = new EventSource("http://localhost:8080/profiler/marks");

  private marks: CpuProfileResult[] = [];
  // private history: CpuProfileResult[] = [
  //   // {
  //   //   id: 0,
  //   //   name: "Root",
  //   //   delta: 1.0,
  //   //   children: [
  //   //     {
  //   //       id: 0,
  //   //       name: "example 1",
  //   //       delta: 0.25,
  //   //       children: [],
  //   //       start: 0,
  //   //       end: 0.25,
  //   //     },
  //   //     {
  //   //       id: 0,
  //   //       name: "example 2",
  //   //       delta: 0.25,
  //   //       children: [],
  //   //       start: 0,
  //   //       end: 0.25,
  //   //     },
  //   //     {
  //   //       id: 0,
  //   //       name: "example 3",
  //   //       delta: 0.25,
  //   //       children: [],
  //   //       start: 0.25,
  //   //       end: 0.5,
  //   //     },
  //   //     {
  //   //       id: 0,
  //   //       name: "example 4",
  //   //       delta: 0.25,
  //   //       children: [
  //   //         {
  //   //           id: 0,
  //   //           name: "example 4",
  //   //           delta: 0.25,
  //   //           children: [],
  //   //           start: 0,
  //   //           end: 0.25,
  //   //         },
  //   //
  //   //         {
  //   //           id: 0,
  //   //           name: "example 4",
  //   //           delta: 0.25,
  //   //           children: [],
  //   //           start: 0,
  //   //           end: 0.25,
  //   //         }
  //   //       ],
  //   //       start: 0,
  //   //       end: 0.25,
  //   //     }
  //   //   ],
  //   //   start: 0,
  //   //   end: 1.0,
  //   // }
  // ];
  private current: CpuProfileResult = {
    id: 0,
    name: "Root",
    delta: 1.0,
    children: [
      {
        id: 0,
        name: "example 1",
        delta: 0.25,
        children: [],
        start: 0,
        end: 0.25,
      },
      {
        id: 0,
        name: "example 2",
        delta: 0.25,
        children: [],
        start: 0,
        end: 0.25,
      },
      {
        id: 0,
        name: "example 3",
        delta: 0.25,
        children: [],
        start: 0,
        end: 0.25,
      },
      {
        id: 0,
        name: "example 4",
        delta: 0.25,
        children: [
          {
            id: 0,
            name: "example 4",
            delta: 0.25,
            children: [],
            start: 0,
            end: 0.25,
          },

          {
            id: 0,
            name: "example 4",
            delta: 0.25,
            children: [],
            start: 0,
            end: 0.25,
          }
        ],
        start: 0,
        end: 0.25,
      }
    ],
    start: 0,
    end: 0.25,
  };

  // private get allMarks(): ProfileMarkDelta[] {
  //   return Object.entries(this.marks).map(([name, delta], index) => ({
  //     name,
  //     delta: (delta * 1000).toFixed(5),
  //     index,
  //   }));
  // }
  private interval?: number;

  public mounted(): void {
    this.profileSource.addEventListener("cpu_profile", this);
  }

  public handleEvent(ev: MessageEvent<string>): void {
    const output = prepareCpuProfileData(JSON.parse(ev.data))[0];
    this.marks.push(output);

    this.$nextTick(() => {
      const result = this.marks.pop();
      if (result) {
        this.current = result;
        // this.history.push(result);
      }
    });
  }

  public beforeDestroy(): void {
    clearInterval(this.interval);
  }
}
</script>
