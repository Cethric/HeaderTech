<template>
  <b-table-simple hover small striped>
    <b-thead>
      <b-tr>
        <b-th>Name</b-th>
        <b-th>Delta (ms)</b-th>
      </b-tr>
    </b-thead>
    <b-tbody>
      <b-tr v-for="mark in marks" :key="mark.index">
        <b-td>{{ mark.name }}</b-td>
        <b-td>{{ mark.delta }}</b-td>

        <b-td>
          <b-collapse visible>
            <TimingMarksTable :marks="mark.children" />
          </b-collapse>
        </b-td>
      </b-tr>
    </b-tbody>
  </b-table-simple>
</template>

<script lang="ts">
import { Component, Prop, Vue } from "vue-property-decorator";
import { ProfileMark } from "@/components/profiles/types";

@Component({})
export default class TimingMarksTable extends Vue {
  @Prop()
  private marks!: ProfileMark[];
}
</script>

<style scoped></style>
