<template>
  <b-container class="profiles">
    <b-row>
      <b-col cols="12">
        <PieChart :data="allMarks" />
      </b-col>
    </b-row>
    <b-row>
      <b-table-simple dark hover small striped>
        <b-thead>
          <b-tr>
            <b-th>Name</b-th>
            <b-th>Delta (ms)</b-th>
          </b-tr>
        </b-thead>
        <b-tbody>
          <b-tr v-for="mark in allMarks" :key="mark.index">
            <b-td>{{ mark.name }}</b-td>
            <b-td>{{ mark.delta }}</b-td>
          </b-tr>
        </b-tbody>
      </b-table-simple>
    </b-row>
  </b-container>
</template>

<style lang="scss" scoped></style>

<script lang="ts">
import { Component, Vue } from "vue-property-decorator";
import PieChart from "@/components/PieChart.vue";

interface ProfileMark {
  name: string;
  delta: number;
}

@Component({
  components: { PieChart }
})
export default class Profiles extends Vue {
  private readonly profileSource: EventSource = new EventSource(
      "http://localhost:8080/profiler/marks"
  );

  private marks: { [name: string]: number } = {};

  private get allMarks(): { name: string; delta: string; index: number }[] {
    return Object.entries(this.marks).map(([name, delta], index) => ({
      name,
      delta: (delta * 1000).toFixed(5),
      index
    }));
  }

  public mounted() {
    this.profileSource.onmessage = ev => {
      this.pushMessage(ev.lastEventId, JSON.parse(ev.data));
    };
  }

  private pushMessage(_: string, mark: ProfileMark) {
    this.$nextTick(() => {
      this.marks = { ...this.marks, [mark.name]: mark.delta };
    });
  }
}
</script>
