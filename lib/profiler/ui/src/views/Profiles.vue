<template>
  <b-container class="profiles">
    <b-row>
      <b-col cols="12">
        <MultilevelTreeMap :data="history" />
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
import { ProfileMark } from "@/components/profiles/types";
import MultilevelTreeMap from "@/components/profiles/MultilevelTreeMap.vue";

@Component({
  components: { MultilevelTreeMap, TimingMarksTable }
})
export default class Profiles extends Vue {
  private readonly profileSource: EventSource = new EventSource("http://localhost:8080/profiler/marks");

  private marks: ProfileMark[] = [];
  private history: ProfileMark = {
    name: "example",
    delta: 1.0,
    children: [
      {
        name: "example 1",
        delta: 0.25,
        children: [],
      },
      {
        name: "example 2",
        delta: 0.25,
        children: [],
      },
      {
        name: "example 3",
        delta: 0.25,
        children: [],
      },
      {
        name: "example 4",
        delta: 0.25,
        children: [],
      },
    ],
  };

  // private get allMarks(): ProfileMarkDelta[] {
  //   return Object.entries(this.marks).map(([name, delta], index) => ({
  //     name,
  //     delta: (delta * 1000).toFixed(5),
  //     index,
  //   }));
  // }
  private interval: number;

  public mounted(): void {
    this.profileSource.onmessage = (ev) => this.pushMessage(ev.lastEventId, JSON.parse(ev.data));
    this.interval = setInterval(this.pushHistory, 10000);
  }

  public beforeDestroy(): void {
    clearInterval(this.interval);
  }

  private pushMessage(_: string, mark: ProfileMark): void {
    this.marks.push(mark);
  }

  private pushHistory(): void {
    this.$nextTick(() => {
      const result = this.marks.pop();
      if (result) {
        this.history = result;
      }
    });
  }
}
</script>
